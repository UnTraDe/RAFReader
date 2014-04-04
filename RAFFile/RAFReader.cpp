#include "RAFReader.h"

#include <zlib.h>
#include <boost/filesystem.hpp>

RAFReader *RAFReader::instance = NULL;

RAFReader *RAFReader::getInstance()
{
	if (instance == NULL)
		instance = new RAFReader();

	return instance;
}

void RAFReader::extractRAF(std::ifstream &file_table, std::ifstream &file_data)
{
	std::vector<PathEntry> pathList;
	std::vector<FileEntry> fileList;

	if (file_table.is_open())
	{
		/* Read file info */

		int magicNum = 0;
		int version = 0;
		int managerIndex = 0;
		int fileListOffest = 0;
		int pathListOffest = 0;

		file_table.read((char*)&magicNum, 4);
		file_table.read((char*)&version, 4);
		file_table.read((char*)&managerIndex, 4);
		file_table.read((char*)&fileListOffest, 4);
		file_table.read((char*)&pathListOffest, 4);

		/* Read file list */

		int fileCount = 0;
		file_table.read((char*)&fileCount, 4);

		for (int i = 0; i < fileCount; i++)
		{
			FileEntry file;
			file_table.read((char*)&file.pathHash, 4);
			file_table.read((char*)&file.dataOffset, 4);
			file_table.read((char*)&file.dataSize, 4);
			file_table.read((char*)&file.pathListIndex, 4);
			fileList.push_back(file);
		}

		/* Read path list */

		file_table.seekg(pathListOffest);

		int pathListSize = 0;
		int pathListCount = 0;

		file_table.read((char*)&pathListSize, 4);
		file_table.read((char*)&pathListCount, 4);


		for (int i = 0; i < pathListCount; i++)
		{
			PathEntry path;
			file_table.read((char*)&path.offest, 4);
			file_table.read((char*)&path.length, 4);
			pathList.push_back(path);
		}

		/* Read and save all files */

		int info_files_bytes = 0;

		char *buff = new char[UNCOMPRESS_BUFFER_LENGTH];

		for (unsigned int i = 0; i < fileList.size(); i++)
		{
			PathEntry path = pathList[fileList[i].pathListIndex];
			char *filePath = new char[path.length];
			char *fileData = new char[fileList[i].dataSize];

			file_table.clear();
			file_table.seekg(pathListOffest + path.offest);
			file_table.read(filePath, path.length);

			file_data.clear();
			file_data.seekg(fileList[i].dataOffset);
			file_data.read(fileData, fileList[i].dataSize);

			int len = UNCOMPRESS_BUFFER_LENGTH;
			uncompress((Bytef*)buff, (uLongf*)&len, (Bytef*)fileData, fileList[i].dataSize);

			std::string dirPath;
			std::vector<std::string> p = split(filePath, '/');

			for (unsigned int j = 0; j < p.size() - 1; j++)
				dirPath += p[j] + '/';

			try
			{
				boost::filesystem::create_directories(dirPath);
			}
			catch (boost::filesystem::filesystem_error &e)
			{
				std::cout << e.code().message() << std::endl;
			}

			std::ofstream out(filePath, std::ios::binary);
			out.write(buff, len);

			info_files_bytes += len;

			//std::cout << filePath << " - " << i+1 << '/' << fileList.size() << std::endl;

			delete filePath;
			delete fileData;
		}

		delete buff;

		/* Print file info */
		/*
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Extraction Finished!" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "File Info:" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Magic Number: " << magicNum << std::endl;
		std::cout << "Version: " << version << std::endl;
		std::cout << "Manager Index: " << managerIndex << std::endl;
		std::cout << "File List Offest: " << fileListOffest << std::endl;
		std::cout << "Path List Offest: " << pathListOffest << std::endl;
		std::cout << "File Count: " << fileCount << std::endl;
		std::cout << "Path Count: " << pathList.size() << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Summary:" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "Files Extracted: " << fileList.size() << std::endl;
		std::cout << "Total bytes written to disk: " << info_files_bytes << std::endl;
		*/
	}
}

void RAFReader::extractAllRAF(const char *path)
{
	boost::filesystem::path rafRoot(path);
	boost::filesystem::directory_iterator end_iter;
	std::vector<boost::filesystem::path> directories;

	for (boost::filesystem::directory_iterator dir_iter(rafRoot); dir_iter != end_iter; ++dir_iter)
	{
		if (boost::filesystem::is_directory(dir_iter->status()))
			directories.push_back(*dir_iter);
	}

	for (unsigned int i = 0; i < directories.size(); i++)
	{
		boost::filesystem::path dir(directories[i]);
		boost::filesystem::directory_iterator end_iter;

		for (boost::filesystem::directory_iterator dir_iter(dir); dir_iter != end_iter; ++dir_iter)
		{
			boost::filesystem::path file(*dir_iter);

			if (boost::filesystem::is_directory(file))
				continue;

			if (!(file.extension() == ".raf"))
				continue;

			std::string f(file.string());

			std::cout << "Extracting " << file.filename() << "..." << std::endl;

			std::ifstream file_table(f, std::ios::binary);
			std::ifstream file_data(f.append(".dat"), std::ios::binary);


			if (file_table.is_open() && file_data.is_open())
				extractRAF(file_table, file_data);
			else
				std::cout << "Error openning " << file.filename() << std::endl;

			file_table.close();
			file_data.close();
		}
	}
}
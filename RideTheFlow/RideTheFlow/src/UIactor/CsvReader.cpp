#include "CsvReader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

// �R���X�g���N�^
CsvReader::CsvReader() {
}

// �R���X�g���N�^
CsvReader::CsvReader(const std::string& fileName) {
	load(fileName);
}

// �t�@�C���̓ǂݍ���
void CsvReader::load(const std::string& fileName) {
	std::ifstream file(fileName);
	if (!file) throw std::runtime_error("CSV�t�@�C�����I�[�v���ł��܂���ł���");
	rows_.clear();
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string value;
		Row row;
		while (std::getline(ss, value, ',')) {
			row.push_back(value);
		}
		rows_.push_back(row);
	}
}

// �f�[�^�̎擾
const std::string& CsvReader::get(int row, int column) const {
	return rows_[row][column];
}

// �f�[�^�̎擾
int CsvReader::geti(int row, int column) const {
	return std::stoi(get(row, column));
}

// �f�[�^�̎擾
float CsvReader::getf(int row, int column) const {
	return std::stof(get(row, column));
}

// �s����Ԃ�
int CsvReader::rows() const {
	return (int)rows_.size();
}

// �񐔂�Ԃ�
int CsvReader::columns(int row) const {
	return (int)rows_[row].size();
}
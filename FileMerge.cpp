#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>

//Caminho completo da pasta que estão os txt
#define caminho "C:\\TESLA\\codigo\\merging\\Teste_3"

//Nome do arquivo que será gerado (pode ser txt ou csv)
#define output_arq_name "merge.xlsx"

//Nome dos arquivos base (não se preocupe com os números)
#define arq_name "ARQ"

//Tipo dos arquivos base
#define arq_type ".txt"

//Retorna o número de arquivos na pasta do caminho (pode ser txt ou csv)
int num_files() {
    std::string folderPath = caminho;

    DIR* directory = opendir(folderPath.c_str());
    if (directory == nullptr) {
        std::cerr << "Erro ao abrir a pasta." << std::endl;
        return 1;
    }

    struct dirent* entry;
    int txtFileCount = 0;

    while ((entry = readdir(directory)) != nullptr) {
        std::string fileName = entry->d_name;
        if (fileName.length() >= 4 && fileName.substr(fileName.length() - 4) == arq_type) {
            txtFileCount++;
        }
    }

    closedir(directory);

    return txtFileCount;
}

int main() {

    int n = num_files();

    //cria um vector com todos os arquivos
    std::vector<std::string> filenames;
    std::string aux_filenames;
    int x = 0;
    std::cout << "Adicionando aquirvo:" << std::endl;
    for (int i = 0; i < n; i++) {
        if (i < 10)
            aux_filenames = arq_name + std::to_string(x) + std::to_string(i) + arq_type;
        else
            aux_filenames = arq_name + std::to_string(i) + arq_type;
        filenames.push_back(aux_filenames);
        std::cout << aux_filenames << std::endl;
    }

    std::ofstream fileOutput(output_arq_name, std::ios::out);

    for(int i = 0; i < n; i++) {
        std::ifstream arq(filenames[i]);
        std::string line;
        int pos_line = 0;
        if(arq.is_open()) {
            while (!arq.eof()) {
                if(pos_line == 0 && i != 0) {
                    std::getline (arq, line);
                    pos_line = 1;
                }
                else {
                    std::getline (arq, line);
                    //std::cout << line << std::endl;
                    fileOutput << line << std::endl;
                }
            }
        }
        arq.close();
    }
    
    fileOutput.close();

    return 0;
}

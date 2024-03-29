/*
Author: leonardodesarocha
leonardodesarocha@gmail.com

Este código tem como objetivo realizar a junção
dos arquivos de saída de um Datalogger.

Ele é capaz de lidar com diferentes tipos de arquivos,
tais como .txt, .csv, .xlsx e outros.

Tanto os arquivos de entrada quanto o arquivo
de saída podem ser nos formatos acima citados.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <dirent.h>

//Caminho dos Arquivos que serão juntados
#define FOLDER_PATH "C:\\TESLA\\codigo\\DataloggerFileMerge"

//Nome do arquivo que será gerado (csv, txt, xlsx, etc)
#define OUTPUT_FILE_NAME "merge.csv"

//Nome dos arquivos base (não se preocupe com os números)
#define ARQ_NAME "ARQ"

//Tipo dos arquivos base (csv, txt, xlsx, etc)
#define ARQ_TYPE ".txt"

//Retorna o número de arquivos na pasta do caminho (pode ser txt ou csv)
int FileNumber() {
    std::string folderPath = FOLDER_PATH; // Caminho para a pasta

    DIR* directory = opendir(folderPath.c_str()); // Abre o diretório
    if (directory == nullptr) {
        std::cout << "Erro ao abrir a pasta" << std::endl; // Mensagem de erro se a pasta não puder ser aberta
        return 1; // Retorna 1 para indicar um erro
    }

    struct dirent* entry; // Estrutura para armazenar informações da entrada de diretório
    int arqFileCount = 0; // Contador para arquivos com a extensão especificada

    while ((entry = readdir(directory)) != nullptr) {
        std::string fileName = entry->d_name; // Obtém o nome do arquivo/diretório atual

        if (fileName.length() >= 4 && fileName.substr(fileName.length() - 4) == ARQ_TYPE) {
            // Verifica se o nome do arquivo tem pelo menos 4 caracteres (para garantir que tenha uma extensão)
            // Verifica se os últimos 4 caracteres do nome do arquivo correspondem à extensão especificada (ARQ_TYPE)
            arqFileCount++; // Incrementa o contador de arquivos
        }
    }

    closedir(directory); // Fecha o diretório

    return arqFileCount; // Retorna o número total de arquivos com a extensão especificada
}

int main() {

    int fileNumber = FileNumber();

    // Cria um vector com todos os arquivos
    std::vector<std::string> fileNames;
    std::string aux_fileNames;
    int x = 0;
    std::cout << "Adicionando arquivo:" << std::endl;

    // Loop para gerar os nomes dos arquivos e adicioná-los ao vetor
    for (int i = 0; i < fileNumber; i++) {
        if (i < 10)
            aux_fileNames = ARQ_NAME + std::to_string(x) + std::to_string(i) + ARQ_TYPE;
        else
            aux_fileNames = ARQ_NAME + std::to_string(i) + ARQ_TYPE;
        fileNames.push_back(aux_fileNames);
        std::cout << aux_fileNames << std::endl;
    }

    // Abre o arquivo de saída para escrita
    std::ofstream fileOutput(OUTPUT_FILE_NAME, std::ios::out);

    // Loop para processar cada arquivo presente no vetor fileNames
    for (int i = 0; i < fileNumber; i++) {
        std::ifstream arq(fileNames[i]); // Abre o arquivo em modo leitura
        std::string line;
        int pos_line = 0;

        // Verifica se o arquivo foi aberto corretamente
        if (arq.is_open()) {
            // Loop para ler cada linha do arquivo e escrevê-las no arquivo de saída
            while (!arq.eof()) {
                if (pos_line == 0 && i != 0) {
                    std::getline(arq, line); // Lê a linha (ignorando cabeçalho dos arquivos a partir do segundo)
                    pos_line = 1;
                } else {
                    std::getline(arq, line); // Lê a linha
                    fileOutput << line << std::endl; // Escreve a linha no arquivo de saída
                }
            }
        }
        arq.close(); // Fecha o arquivo atual
    }
    
    fileOutput.close(); // Fecha o arquivo de saída

    return 0; // Encerra o programa
}
#pragma once

#include <fstream>
#include <memory.h>

class FileSerializer {
public:
  FileSerializer() = delete;
  ~FileSerializer() = delete;

  template <typename T> static void Serialize(T *data, const char *filePath) {
    char buffer[sizeof(T)];
    memcpy(&buffer, data, sizeof(T));

    std::ofstream file(filePath, std::ios::binary | std::ios::out);
    if (file) {
      file.write(buffer, sizeof(buffer));
      file.close();
    }
  }

  template <typename T> static void Deserialize(T *data, const char *filePath) {
    char buffer[sizeof(T)];

    std::ifstream file(filePath, std::ios::binary | std::ios::in);
    if (file) {
      file.read((char *)&buffer, sizeof(buffer));
      file.close();
    }

    memcpy(data, &buffer, sizeof(T));
  }
};

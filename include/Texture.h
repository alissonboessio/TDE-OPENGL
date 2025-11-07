#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture {
private:

public:
    unsigned int ID;
    int width, height, nrChannels;
    Texture(const std::string& path, bool flip = true);
    ~Texture();

    void bind(unsigned int unit = 0) const;
};

#endif

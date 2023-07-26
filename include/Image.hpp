#pragma once
#include <glad/glad.h>
#include "stb_image.h"
#include<iostream>

namespace MY_IMAGE
{
    class Image
    {
        private:
            unsigned char* data;
            int width;
            int height;
            int nrChannels;
        public:
            Image(const char* path)
            {
                data = stbi_load(path, &width, &height, &nrChannels, 0);
                if(!data)
                    std::cout << "Failed to load Image" << std::endl;
                else
                    std::cout << "Loaded Image" << std::endl;
            }
            ~Image()
            {
                stbi_image_free(data);
            }
            unsigned char* getData()
            {
                return data;
            }
            int getWidth()
            {
                return width;
            }
            int getHeight()
            {
                return height;
            }
            int getNrChannels()
            {
                return nrChannels;
            }

    };

    class Texture
    {
        private:
            unsigned int textureId;
        public:
            Texture(const char* path)
            {
                glGenTextures(1, &textureId);
                glBindTexture(GL_TEXTURE_2D, textureId);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
                Image image(path);
                if (image.getData())
                {
                    int image_type = image.getNrChannels() == 3 ? GL_RGB : GL_RGBA;
                    glTexImage2D(GL_TEXTURE_2D, 0, image_type, image.getWidth(), image.getHeight(), 0, image_type, GL_UNSIGNED_BYTE, image.getData());
                    glGenerateMipmap(GL_TEXTURE_2D);
                }
                else
                {
                    std::cout << "Failed to load texture" << std::endl;
                }
            }
            ~Texture()
            {
                glDeleteTextures(1, &textureId);
            }
            void bind()
            {
                glBindTexture(GL_TEXTURE_2D, textureId);
            }
    };
}

#pragma once

#include<glad/glad.h>
#include<iostream>

namespace BUFFER_OBJECT
{
    typedef unsigned int VBO_ID_TYPE;
    typedef unsigned int VAO_ID_TYPE;
    typedef unsigned int EBO_ID_TYPE;
    constexpr VBO_ID_TYPE INVALID_VBO_ID = 0;
    constexpr VAO_ID_TYPE INVALID_VAO_ID = 0;
    constexpr EBO_ID_TYPE INVALID_EBO_ID = 0;
    class VBO
    {
        private:
            VBO_ID_TYPE vboID;
        public:
            VBO()
            {
                glGenBuffers(1, &vboID);
            }

            /**
             * @brief 
             * bind this VBO
             */
            void bind()
            {
                if(vboID != INVALID_VBO_ID)
                    glBindBuffer(GL_ARRAY_BUFFER, vboID);
                else std::cout << "ERROR::BUFFER_OBJECT::VBO::BIND::VBO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * unbind 
             */
            static void unbind()
            {
                glBindBuffer(GL_ARRAY_BUFFER, INVALID_VBO_ID);
            }

            /**
             * @brief 
             * delete this VBO
             */
            void deleteVBO()
            {
                if(vboID != INVALID_VBO_ID)
                {
                    glDeleteBuffers(1, &vboID);
                    vboID = INVALID_VBO_ID;
                }
                else std::cout << "ERROR::BUFFER_OBJECT::VBO::DELETE_VBO::VBO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * @return VBO_ID_TYPE 
             */
            VBO_ID_TYPE getVBOID()
            {
                return vboID;
            }

            /**
             * @brief 
             * create a VBO
             */

            void createVBO()
            {
                if(vboID == INVALID_VBO_ID)
                glGenBuffers(1, &vboID);
                else std::cout << "ERROR::BUFFER_OBJECT::VBO::CREATE_VBO::VBO_ALREADY_CREATED" << std::endl;
            }

            /**
             * @brief 
             * @param size 数组所占用的空间
             * @param data 数组地址
             * @param usage 如何管理给定的数据(STATIC_DRAW, DYNAMIC_DRAW, STREAM_DRAW)
             */
            void setBufferData(GLsizeiptr size, const void* data, GLenum usage)
            {
                glBufferData(GL_ARRAY_BUFFER, size, data, usage);
            }
    };

    class VAO
    {
        private:
            VAO_ID_TYPE vaoID;
        public:
            VAO()
            {
                glGenVertexArrays(1, &vaoID);
            }

            /**
             * @brief 
             * bind this VAO
             */
            void bind()
            {
                if(vaoID != INVALID_VAO_ID)
                    glBindVertexArray(vaoID);
                else std::cout << "ERROR::BUFFER_OBJECT::VAO::BIND::VAO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * unbind this VAO
             */
            static void unbind()
            {
                glBindVertexArray(INVALID_VAO_ID);
            }

            /**
             * @brief 
             * delete this VAO
             */
            void deleteVAO()
            {
                if(vaoID != INVALID_VAO_ID)
                {
                    glDeleteVertexArrays(1, &vaoID);
                    vaoID = INVALID_VAO_ID;
                }
                else std::cout << "ERROR::BUFFER_OBJECT::VAO::DELETE_VAO::VAO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * @return VAO_ID_TYPE 
             */
            VAO_ID_TYPE getVAOID()
            {
                return vaoID;
            }

            /**
             * @brief 
             * create a VAO
             */
            void createVAO()
            {
                if(vaoID == INVALID_VAO_ID)
                    glGenVertexArrays(1, &vaoID);
                else std::cout << "ERROR::BUFFER_OBJECT::VAO::CREATE_VAO::VAO_ALREADY_CREATED" << std::endl;
            }

            /**
             * @brief 链接顶点属性
             * @attention 每个顶点属性从一个VBO管理的内存中获得它的数据，而具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。由于在调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
             * @param index 配置顶点属性
             * @param size 属性的大小(不是占用的空间)
             * @param type (GL_FLOAT, GL_INT, GL_UNSIGNED_INT)
             * @param normalized 是否希望被标准化
             * @param stride 步长,在连续的顶点属性组之间的间隔(单位是字节)
             * @param pointer 表示偏移量
             */
            void setVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
            {
                glVertexAttribPointer(index, size, type, normalized, stride, pointer);
                glEnableVertexAttribArray(index);
            }
    };

    class EBO
    {
        private:
            EBO_ID_TYPE eboID;
        public:
            EBO()
            {
                glGenBuffers(1, &eboID);
            }

            /**
             * @brief 
             * bind this EBO
             */
            void bind()
            {
                if(eboID != INVALID_EBO_ID)
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
                else std::cout << "ERROR::BUFFER_OBJECT::EBO::BIND::EBO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * unbind this EBO
             */
            static void unbind()
            {
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, INVALID_EBO_ID);
            }

            /**
             * @brief 
             * delete this EBO
             */
            void deleteEBO()
            {
                if(eboID != INVALID_EBO_ID)
                {
                    glDeleteBuffers(1, &eboID);
                    eboID = INVALID_EBO_ID;
                }
                else std::cout << "ERROR::BUFFER_OBJECT::EBO::DELETE_EBO::EBO_ALREADY_DELETED" << std::endl;
            }

            /**
             * @brief 
             * @return EBO_ID_TYPE 
             */
            EBO_ID_TYPE getEBOID()
            {
                return eboID;
            }

            /**
             * @brief 
             * create a EBO
             */
            void createEBO()
            {
                if(eboID == INVALID_EBO_ID)
                    glGenBuffers(1, &eboID);
                else std::cout << "ERROR::BUFFER_OBJECT::EBO::CREATE_EBO::EBO_ALREADY_CREATED" << std::endl;
            }

            /**
             * @brief 
             * @param size 数组所占用的空间
             * @param data 数组地址
             * @param usage 如何管理给定的数据(STATIC_DRAW, DYNAMIC_DRAW, STREAM_DRAW)
             */
            void setBufferData(GLsizeiptr size, const void* data, GLenum usage)
            {
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
            }

    };
}
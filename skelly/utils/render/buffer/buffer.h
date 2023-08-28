#pragma once

#ifndef PCH_ENABLED
    #include <defs.h>
    #include <logger.h>
#endif

namespace skelly {

    enum class ShaderDataType {
        None = 0,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type) {
        switch(type) {
            case ShaderDataType::Float: return sizeof(float);
            case ShaderDataType::Float2: return sizeof(float)*2;
            case ShaderDataType::Float3: return sizeof(float)*3;
            case ShaderDataType::Float4: return sizeof(float)*4;
            case ShaderDataType::Mat3: return sizeof(float)*3*3;
            case ShaderDataType::Mat4: return sizeof(float)*4*4;
            case ShaderDataType::Int: return sizeof(int);
            case ShaderDataType::Int2: return sizeof(int)*2;
            case ShaderDataType::Int3: return sizeof(int)*3;
            case ShaderDataType::Int4: return sizeof(int)*4;
            case ShaderDataType::Bool: return sizeof(char);
            default:
                SKELLY_ASSERT(false, "ShaderDataTypeSize: Unknown ShaderDataType");
                return 0;
        }

        SKELLY_ASSERT(false, "ShaderDataTypeSize: Unknwown Error");
        return 0;
    }

    struct BufferElement {
        ShaderDataType type;
        std::string name;
        uint32_t size;
        uint32_t offset;
        bool isNormalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string name, bool isNormalized = false) : 
            type(type), name(name), size(ShaderDataTypeSize(type)), offset(0), isNormalized(isNormalized) {}

        uint32_t getComponentCount() const {
            switch(type) {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;
                case ShaderDataType::Mat3: return 3*3;
                case ShaderDataType::Mat4: return 4*4;
                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;
                case ShaderDataType::Bool: return 1;
                default:
                    SKELLY_ASSERT(false, "BufferElement::getElementCount: Unknown Shader Data Type.");
                    return 0;
            }
        }
    };

    class BufferLayout {
        public:
            BufferLayout(const std::initializer_list<BufferElement>& elements) : _m_elements(elements) {
                calculateOffsetsAndStride();
            }

            BufferLayout() {}

            inline const std::vector<BufferElement>& getElements() const { return _m_elements; }
            inline uint32_t getStride() const { return _m_stride; }

            std::vector<BufferElement>::iterator begin() { return _m_elements.begin(); }
            std::vector<BufferElement>::iterator end() { return _m_elements.end(); }
            std::vector<BufferElement>::const_iterator begin() const { return _m_elements.begin(); }
            std::vector<BufferElement>::const_iterator end() const { return _m_elements.end(); }
        private:

            void calculateOffsetsAndStride() {
                uint32_t offset = 0;
                _m_stride = 0;
                for (auto& element : _m_elements) {
                    element.offset = offset;
                    offset += element.size;
                    _m_stride += element.size;
                }
            }

            std::vector<BufferElement> _m_elements;
            uint32_t _m_stride = 0;
    };

    class VertexBuffer {
        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual const BufferLayout& getLayout() const = 0;
            virtual void setLayout(const BufferLayout& layout) = 0;

            static VertexBuffer* create(float* vertices, uint32_t size);
    };

    class IndexBuffer {
        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;

            virtual uint32_t getCount() const = 0;

            static IndexBuffer* create(uint32_t* indices, uint32_t size);
    };

}
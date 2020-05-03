#ifndef __REVSHADER_H__
#define __REVSHADER_H__

#include "revDevice.h"
#include "revResource.h"

enum class SHADER_TYPE : uint32
{
	VERTX,
	FRAGMENT,
	COMPUTE,
	MAX_NUM,
};

// rev use vertex only buffer for optimization
// quotes: galaxy game dev
class revAttributeBinding
{
public:
    revAttributeBinding():
		type(0),
		binding(0),
		format(0),
		offset(0)
	{}

	INPUT_ELEMENT_TYPE GetInputElementType() const { return static_cast<INPUT_ELEMENT_TYPE>(type); }
    uint8 GetBinding() const { return binding; }
    uint8 GetLocation() const { return static_cast<uint32>(type); }
    GRAPHICS_FORMAT GetForamt() const { return static_cast<GRAPHICS_FORMAT>(format); }
    uint8 GetOffset() const { return offset; }
	INPUT_CLASS GetInputClass() const { return static_cast<INPUT_CLASS>(inputClass); }

#ifdef _DEBUG
	void SetInputElementType(INPUT_ELEMENT_TYPE _type) { type = static_cast<uint8>(_type); }
	void SetBinding(uint8 _binding) { binding = _binding; }
	void SetFormat(GRAPHICS_FORMAT _format) { format = static_cast<uint8>(_format); }
	void SetOffset(uint8 _offset) { offset = _offset; }
	void SetInputClass(INPUT_CLASS _class) { inputClass = static_cast<uint8>(_class); }
#endif


	SERIALIZE_FUNC()
	{
		archive(REV_NVP(type),
			REV_NVP(binding),
			REV_NVP(format),
			REV_NVP(offset),
			REV_NVP(inputClass)
		);
	}

private:
	uint8 type;
    uint8 binding;
    uint8 format;
    uint8 offset;
	uint8 inputClass;
};

class revConstantBufferBinding
{
public:
	uint8 GetRegisterIndex() const { return registerIndex; }
#ifdef _DEBUG
	void SetRegisterIndex(uint8 index) { registerIndex = index; }
#endif

	SERIALIZE_FUNC()
	{
		archive(REV_NVP(registerIndex)
		);
	}
private:
	uint8 registerIndex;
};

class revTextureBinding
{
public:
	revTextureBinding():
		registerIndex(0),
		count(0),
		space(0),
		is3d(false)
	{}

	SERIALIZE_FUNC()
	{
		archive(REV_NVP(registerIndex),
			REV_NVP(count),
			REV_NVP(space),
			REV_NVP(is3d)
		);
	}

	uint8 GetRegisterIndex() const { return registerIndex; }
	uint8 GetCount() const { return count; }
	uint8 GetSpace() const { return space; }
	bool Is3d() const { return is3d; }
#ifdef _DEBUG
	void SetRegisterIndex(uint8 index) { registerIndex = index; }
	void SetCount(uint8 count) { this->count = count; }
	void SetSpace(uint8 space) { this->space = space; }
	void Set3d(bool flag) { is3d = flag; }
#endif

private:
	uint8 registerIndex;
	uint8 count;
	uint8 space;
	bool is3d;
};

class revSamplerBinding
{
public:
	revSamplerBinding() :
		registerIndex(0),
		count(0),
		space(0)
	{
	}
	uint8 GetRegisterIndex() const { return registerIndex; }
	uint8 GetCount() const { return count; }
	uint8 GetSpace() const { return space; }

#ifdef _DEBUG
	void SetRegisterIndex(uint8 index) { registerIndex = index; }
	void SetCount(uint8 count) { this->count = count; }
	void SetSpace(uint8 space) { this->space = space; }
#endif

	SERIALIZE_FUNC()
	{
		archive(REV_NVP(registerIndex),
			REV_NVP(count),
			REV_NVP(space)
		);
	}
private:
	uint8 registerIndex;
	uint8 count;
	uint8 space;
	bool is3d;
};


class revShader : public revResource
{
public:
	revShader() :
		type(SHADER_TYPE::VERTX),
		name("")
	{
	}
	virtual ~revShader(){}
	virtual bool LoadFromFile(const revDevice& deviceContext, const char* path, SHADER_TYPE shaderType) = 0;
	revShaderHandle GetHandle() const { return handle; }
	const revArray<revAttributeBinding>& GetAttributes() const { return metaData.attributes; }
	const revArray<revConstantBufferBinding>& GetConstantBuffers() const { return metaData.cbuffers; }
	const revArray<revTextureBinding>& GetTextureBindings() const { return metaData.textures; }
	const revArray<revSamplerBinding>& GetSamplerBindings() const { return metaData.samplers; }

	struct ShaderMetaData
	{
		DefaultMetaData data;
		revArray<revAttributeBinding> attributes;
		revArray<revConstantBufferBinding> cbuffers;
		revArray<revTextureBinding> textures;
		revArray<revSamplerBinding> samplers;
	};
	
protected:
	bool LoadMetaData(const char* path);

	revString name;
    SHADER_TYPE type;
	revShaderHandle handle;
	ShaderMetaData metaData;
    
};


SERIALIZE_FUNC_NON_INTRUSIVE(revShader::ShaderMetaData, metaData)
{
	archive(REV_MAKE_NVP(data, metaData.data),
		REV_MAKE_NVP(attributes, metaData.attributes),
		REV_MAKE_NVP(cbuffers, metaData.cbuffers),
		REV_MAKE_NVP(textures, metaData.textures),
		REV_MAKE_NVP(samplers, metaData.samplers)	
		);
}

#endif
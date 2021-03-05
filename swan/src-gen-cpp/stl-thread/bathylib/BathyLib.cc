#include "bathylib/BathyLib.h"
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace bathylib
{
void BathyLib::jsonInit(const char* jsonContent)
{
	rapidjson::Document document;
	assert(!document.Parse(jsonContent).HasParseError());
	assert(document.IsObject());
	const rapidjson::Value::Object& o = document.GetObject();

	if (o.HasMember("waveFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["waveFilename"];
		assert(valueof_fileName.IsString());
		waveFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("waveVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["waveVarName"];
		assert(valueof_fileName.IsString());
		waveVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("depthFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["depthFilename"];
		assert(valueof_fileName.IsString());
		depthFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("depthVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["depthVarName"];
		assert(valueof_fileName.IsString());
		depthVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("lonFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["lonFilename"];
		assert(valueof_fileName.IsString());
		lonFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("lonVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["lonVarName"];
		assert(valueof_fileName.IsString());
		lonVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("latFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["latFilename"];
		assert(valueof_fileName.IsString());
		latFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("latVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["latVarName"];
		assert(valueof_fileName.IsString());
		latVarName = valueof_fileName.GetString();
	}

	if (o.HasMember("bottomMotionFilename"))
	{
		const rapidjson::Value& valueof_fileName = o["bottomMotionFilename"];
		assert(valueof_fileName.IsString());
		bottomMotionFilename = valueof_fileName.GetString();
	}

	if (o.HasMember("bottomVarName"))
	{
		const rapidjson::Value& valueof_fileName = o["bottomVarName"];
		assert(valueof_fileName.IsString());
		bottomVarName = valueof_fileName.GetString();
	}
}
}

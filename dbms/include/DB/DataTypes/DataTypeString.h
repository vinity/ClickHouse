#pragma once

#include <ostream>

#include <DB/DataTypes/IDataType.h>


namespace DB
{

class DataTypeString final : public IDataType
{
public:
	using FieldType = String;

	std::string getName() const override
	{
		return "String";
	}

	DataTypePtr clone() const override
	{
		return std::make_shared<DataTypeString>();
	}

	void serializeBinary(const Field & field, WriteBuffer & ostr) const override;
	void deserializeBinary(Field & field, ReadBuffer & istr) const override;
	void serializeBinary(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;
	void deserializeBinary(IColumn & column, ReadBuffer & istr) const override;

	void serializeBinary(const IColumn & column, WriteBuffer & ostr, size_t offset = 0, size_t limit = 0) const override;
	void deserializeBinary(IColumn & column, ReadBuffer & istr, size_t limit, double avg_value_size_hint) const override;

	void serializeTextEscaped(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;
	void deserializeTextEscaped(IColumn & column, ReadBuffer & istr) const override;
	void serializeTextQuoted(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;
	void deserializeTextQuoted(IColumn & column, ReadBuffer & istr) const override;

	void serializeText(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;
	void serializeTextXML(const IColumn & column, size_t row_num, WriteBuffer & ostr) const override;

	ColumnPtr createColumn() const override;
	ColumnPtr createConstColumn(size_t size, const Field & field) const override;

	Field getDefault() const override
	{
		return String("");
	}

private:

	void serializeTextJSONImpl(const IColumn & column, size_t row_num, WriteBuffer & ostr, const NullValuesByteMap * null_map) const override;
	void deserializeTextJSONImpl(IColumn & column, ReadBuffer & istr, NullValuesByteMap * null_map) const override;
	void serializeTextCSVImpl(const IColumn & column, size_t row_num, WriteBuffer & ostr, const NullValuesByteMap * null_map) const override;
	void deserializeTextCSVImpl(IColumn & column, ReadBuffer & istr, const char delimiter, NullValuesByteMap * null_map) const override;
};

}

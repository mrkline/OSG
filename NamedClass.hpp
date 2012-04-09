#pragma once

#include <string>

/*!
\brief A useful base class that gives its children a name and ID value
\warning Nothing prevents objects derived from NamedClass to have
         identical names or IDs.
*/
class NamedClass
{
public:
	NamedClass(int cid = -1, const std::string& cName = std::string())
		: id(cid), name(cName)
	{ }

	virtual ~NamedClass() { }

	//! Sets the object's ID
	void SetID(int newID) { id = newID; }
	//! Sets the object's name
	void SetName(const std::string& newName) { name = newName; }
	//! Sets the object's name
	void SetName(const char* newName) { name = newName; }

	//! Gets the object's ID
	int GetID() const { return id; }
	//! Gets the object's name
	const std::string& GetName() const { return name; }
	//! Gets the object's name
	std::string& GetName() { return name; }

protected:
	int id; //!< ID number of the object
	std::string name; //!< Name of the object
};

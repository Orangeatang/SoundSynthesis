
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IObject.h"

#include <rapidxml_print.hpp>


//////////////////////////////////////////////////////////////////////////
/// IObject
//////////////////////////////////////////////////////////////////////////

IObject::IObject()
{
    UuidCreate( &myId );
}

//////////////////////////////////////////////////////////////////////////

IObject::~IObject()
{
}

//////////////////////////////////////////////////////////////////////////

const char* IObject::Serialize() const
{
    rapidxml::xml_document<char> objectDocument;

    // convert the object id to a string
    RPC_CSTR* uuidString = nullptr;
    UuidToString( &myId, uuidString );

    // store the string in an objectid attribute
    rapidxml::xml_node<char>* objectIdNode = objectDocument.allocate_node( rapidxml::node_element, "ObjectID", (char*)uuidString );

    // pass the xml document to child claass instances
    ToXML( objectDocument );

    // return the chararacter array representation of the xml
    std::string objectString;
    rapidxml::print( std::back_inserter(objectString), objectDocument, 0 );

    return objectString.c_str();
}

//////////////////////////////////////////////////////////////////////////

bool IObject::Deserialize( char* anXMLString )
{
    // convert the supplied string to an xml document
    rapidxml::xml_document<char> objectDocument;
    objectDocument.parse<0>( anXMLString );

    // verify that the object IDs match
    rapidxml::xml_node<char>* objectIDNode = objectDocument.first_node( "ObjectID" );
    if( objectIDNode == nullptr )
    {
        return false;
    }

    UUID testUUID;
    UuidFromString( (RPC_CSTR)objectIDNode->value(), &testUUID );
    if( myId != testUUID )
    {
        return false;
    }

    // pass the doucument through to child instances
    return FromXML( objectDocument );
}

//////////////////////////////////////////////////////////////////////////

const UUID& IObject::GetId() const
{
    return myId;
}

//////////////////////////////////////////////////////////////////////////

bool IObject::operator==( const UUID& anId ) const
{
    return (anId == myId);
}

//////////////////////////////////////////////////////////////////////////

bool IObject::operator==( const IObject& anObject ) const
{
    return (anObject.myId == myId);
}

//////////////////////////////////////////////////////////////////////////

bool IObject::operator==( const IObject* anObject ) const
{
    if( anObject == nullptr )
    {
        return false;
    }

    return (anObject->myId == myId);
}

//////////////////////////////////////////////////////////////////////////
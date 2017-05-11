
//////////////////////////////////////////////////////////////////////////
/// Namespaces
//////////////////////////////////////////////////////////////////////////

using namespace System;


//////////////////////////////////////////////////////////////////////////
/// Structures
//////////////////////////////////////////////////////////////////////////

struct CharacterArary
{
public :

    //////////////////////////////////////////////////////////////////////////

    CharacterArary();
    CharacterArary( char* aString );
    CharacterArary( const CharacterArary& anArray );
    ~CharacterArary();

    //////////////////////////////////////////////////////////////////////////

    char* myString;


private :

    //////////////////////////////////////////////////////////////////////////

    int myRefCount;
};


//////////////////////////////////////////////////////////////////////////
/// Functions
//////////////////////////////////////////////////////////////////////////

CharacterArary StringToChar( String^ aString );

//////////////////////////////////////////////////////////////////////////
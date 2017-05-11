
//////////////////////////////////////////////////////////////////////////
/// Includes
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Helpers.h"


//////////////////////////////////////////////////////////////////////////
/// CharacterArray
//////////////////////////////////////////////////////////////////////////

CharacterArary::CharacterArary() :
    myRefCount( 0 ),
    myString( "" )
{
    ++myRefCount;
}

//////////////////////////////////////////////////////////////////////////

CharacterArary::CharacterArary( char* aString ) :
    myString( aString ),
    myRefCount( 0 )
{
    ++myRefCount;
}

//////////////////////////////////////////////////////////////////////////

CharacterArary::~CharacterArary()
{
    --myRefCount;
    if( myRefCount == 0 )
    {
        free( myString );
    }
}

//////////////////////////////////////////////////////////////////////////

CharacterArary::CharacterArary( const CharacterArary& aCharacterArray )
{
    myString = aCharacterArray.myString;
    myRefCount = aCharacterArray.myRefCount;
}

//////////////////////////////////////////////////////////////////////////
/// Functions
//////////////////////////////////////////////////////////////////////////

CharacterArary StringToChar( String^ aString )
{
    // pin memory so GC can't move it while native function is called
    pin_ptr<const wchar_t> wch = PtrToStringChars( aString );

    // convert to char*... don't forget to free the character arrays!
    size_t convertedCharacters  = 0;
    size_t sizeInBytes          = ((aString->Length + 1) * 2);
    errno_t errorCode           = 0;
    char* result                = (char*)malloc(sizeInBytes);

    errorCode = wcstombs_s( &convertedCharacters, result, sizeInBytes, wch, sizeInBytes );
    if( errorCode != 0 )
    {
        return CharacterArary();
    }
    
    return CharacterArary( result );
}
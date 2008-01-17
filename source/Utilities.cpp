/*
* Copyright (c) 2007 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#include "Utilities.h"
#include "BaseObject.h"

namespace SlimDX
{
	/* Unused for now.
	void Utilities::ReportNotDisposed( BaseObject^ obj )
	{
		String^ message = String::Format( CultureInfo::InvariantCulture, "Object of type {0} not disposed.", obj->GetType()->ToString() );
		Debug::WriteLine( message );
	}
	*/
	
	/* Unused for now.
	void Utilities::MarkDisposed( bool %disposed, Object^ obj )
	{
		if( disposed )
			throw gcnew ObjectDisposedException( obj->GetType()->ToString() );

		disposed = true;
		GC::SuppressFinalize( obj );
	}
	*/

	/* Unused for now.
	/// <summary>
	/// Function to convert a GDI+ rectangle to a standard RECT.
	/// </summary>
	/// <param name="rect">Rectangle to convert.</param>
	/// <param name="outrect">Output rectangle.</param>
	void Utilities::ConvertRect(Drawing::Rectangle rect, RECT *outrect)
	{
		if (outrect == NULL)
			throw gcnew ArgumentNullException("outrect");

		outrect->left = rect.Left;
		outrect->top = rect.Top;
		outrect->right = rect.Right;
		outrect->bottom = rect.Bottom;
	}
	*/

	/// <summary>
	/// Function to convert a standard RECT to a GDI+ rectangle.
	/// </summary>
	/// <param name="rect">RECT to convert.</param>
	/// <returns>A GDI+ rectangle structure.</returns>
	Drawing::Rectangle Utilities::ConvertRect(RECT rect)
	{
		return Drawing::Rectangle(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
	}

	array<Byte>^ Utilities::ReadStream( Stream^ stream, int readLength )
	{
		if( stream == nullptr )
			throw gcnew ArgumentNullException( "stream" );
		if( !stream->CanRead )
			throw gcnew NotSupportedException();

		if( readLength == 0 )
			readLength = (int) ( stream->Length - stream->Position );
		if( readLength < 0 )
			throw gcnew ArgumentOutOfRangeException( "readLength" );
		if( readLength == 0 )
			return gcnew array<Byte>( 0 );

		array<Byte>^ buffer = gcnew array<Byte>( readLength ); 
		int bytesRead = 0;

		while( bytesRead < readLength )
		{
			bytesRead += stream->Read( buffer, bytesRead, readLength - bytesRead );
		}

		return buffer;
	}

	generic<typename T>
	void Utilities::CheckArrayBounds( array<T>^ data, int offset, int% count )
	{
		if( count == 0 )
			count = data->Length - offset;

		if( offset < 0 || offset >= data->Length )
			throw gcnew ArgumentOutOfRangeException( "offset" );
		if( count < 0 || count > data->Length - offset )
			throw gcnew ArgumentOutOfRangeException( "count" );
	}

	Guid Utilities::FromGUID( const GUID &guid )
	{
		if( guid == GUID_NULL )
			return Guid::Empty;

		Guid result( guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2], 
			guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7] );

		return result;
	}

	GUID Utilities::ToGUID( Guid guid )
	{
		if( guid == Guid::Empty )
			return GUID_NULL;

		GUID result;
		array<Byte>^ bytes = guid.ToByteArray();
		pin_ptr<unsigned char> pinned_bytes = &bytes[0];
		memcpy( &result, pinned_bytes, sizeof(GUID) );

		return result;
	}

	String^ Utilities::BufferToString( ID3DXBuffer *buffer )
	{
		if( buffer != NULL )
		{
			String^ string = gcnew String( reinterpret_cast<const char*>( buffer->GetBufferPointer() ) );
			buffer->Release();
			return string;
		}
		else
		{
			return String::Empty;
		}
	}
}
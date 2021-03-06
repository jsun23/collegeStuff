#include <cassert>
#include <iomanip>
using namespace std;

#include "hash_lp.h"

Table::Table( )
{
   used = 0;
   for ( int i = 0; i < CAPACITY; i++ )
      table[i].key = -1;
}

void Table::insert( const RecordType& entry )
{
   bool alreadyThere;
   int index;

   assert( entry.key >= 0 );

   findIndex( entry.key, alreadyThere, index );
   if( alreadyThere )
      table[index] = entry;
   else
   {
      assert( size( ) < CAPACITY );
      index = hash( entry.key );
      while ( table[index].key != -1 )
         index = ( index + 1 ) % CAPACITY;
      table[index] = entry;
      used++;
   }
}


int Table::hash( int key ) const
{
   return key % CAPACITY;
}

int Table::size( ) const
{
   return used;
}

// findIndex function
//     void findIndex( int key, bool& found, int &index ) const;
// Preconditions:  key >= 0.
// Postconditions: If a record with the indicated key is in the table,
//    then found is true and index is set to index of the found record.
//    Otherwise, found is false and index is garbage.

void Table::findIndex( int key, bool& found, int& i ) const
{
   int count = 0;

   assert( key >=0 );

   i = hash( key );
   while ( count < CAPACITY && table[i].key != -1 && table[i].key != key )
   {
      count++;
      i = (i + 1) % CAPACITY;
   }
   found = table[i].key == key;
}

void Table::find( int key, bool& found, RecordType& result ) const
{
   int index;

   assert( key >=0 );

   findIndex( key, found, index );
   if ( found )
      result = table[index];
}

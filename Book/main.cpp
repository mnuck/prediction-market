#include <iostream>
#include <stdio.h>

using std::cout;
using std::endl;

#include <Feed.h>
#include <Book.h>

int main(int argc, char* argv[])
{
    Feed f;
    Book b(f);
    
    UniqueID id = b.GetUniqueID();
    Market m(id);
    m.SetDescription("A Thing will happen today.");
    b.OpenMarket(m);
    b.CloseMarket(id, Market::Outcome::TRUE);

	return 0;
}

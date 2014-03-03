// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;

// Begin app, called once at the start
void app::Begin( void )
{
	agk::CreateSprite(1,agk::LoadImage("Basketball.png"));
}// Main loop, called every frame

void app::Loop ( void )
{	
	agk::Sync ( );
}

// Called when the app ends
void app::End ( void )
{
}

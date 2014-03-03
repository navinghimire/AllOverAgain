// Includes, namespace and prototypes
#include "template.h"
using namespace AGK;
app App;
float ballx, bally, xx;
int APPLY_IMPULSE = 0;
int BIRD = 1;
int BOX_IMG = 1;
int BIRD_IMG= 2;
int BOXT_IMG= 4;
int FOR_IMG = 3;
int BACK_IMG = 5;
int x;
int separation = 150;
int boxx = 0;// Begin app, called once at the start
int FOR[2];
float FOR_X[2];
int BOX[5];
int BACK = 100;
float BOX_X[5];
float BOX_Y[5];
int FLAP = 1;
int HIT = 2;
int BOXT[5];
float BOXT_X[5];
float BOXT_Y[5];
int score = 0;
int menuOption = 0;
int PLAY = 1;
void LoadResource(void);
void Initialize(void);


void app::Begin( void )
{
	agk::SetVirtualResolution(640,480);
	agk::SetClearColor(0,0,100);

	LoadResource();
	agk::CreateText(PLAY,"PLAY");
	agk::SetTextSize(PLAY,40);
	agk::SetTextPosition(PLAY,320-agk::GetTextTotalWidth(PLAY)/2,240-agk::GetTextTotalWidth(PLAY)/2);
	agk::SetTextColor(PLAY,255,0,0,255);
	//initialization::


	agk::CreateSprite(BACK,BACK_IMG);
	agk::SetSpriteSize(BACK,640,480);

	//create twitter bird, set its position and enable physics 
	agk::CreateSprite(BIRD, BIRD_IMG);
	agk::SetSpritePosition(BIRD, 50,240);
	agk::SetSpritePhysicsOn(BIRD,2);

	FOR[0] = 20;
	FOR[1] = 21;
	FOR_X[0] = 0;
	FOR_X[1] = 640;
	
	for (int i = 0; i < 5; i++)
	{
		BOX[i] = i + 4;
		BOXT[i] = i + 101;
		agk::CreateSprite(BOX[i],BOX_IMG);
		agk::CreateSprite(BOXT[i],BOXT_IMG);
		x += 168; 
		BOX_X[i] = x; 
		BOXT_X[i] = x; 

		BOX_Y[i] = agk::Random(separation,480);
		BOXT_Y[i] = BOX_Y[i] - separation - 480;
		agk::SetSpritePosition(BOX[i],BOX_X[i],BOX_Y[i]);
		agk::SetSpritePosition(BOXT[i],BOXT_X[i],BOXT_Y[i]);
		agk::SetSpritePhysicsOn(BOXT[i],1);
		agk::SetSpritePhysicsOn(BOX[i],1);
		agk::SetSpriteShape(BOX[i],2);
		agk::SetSpriteShape(BOXT[i],2);
	}

	//physics settings
	agk::CreateSprite(FOR[0],FOR_IMG);
	agk::SetSpritePosition(FOR[0],FOR_X[0],420);

	agk::CreateSprite(FOR[1],FOR_IMG);
	agk::SetSpritePosition(FOR[1],FOR_X[1],420);
	
	agk::SetPhysicsGravity(0,0);
	agk::SetSpriteShape(BIRD,1);
	agk::SetPhysicsWallBottom(0);
	agk::SetSpriteAnimation(BIRD,183,168,14);
	agk::SetSpritePhysicsCanRotate(BIRD,0);
	agk::SetSpriteScale(BIRD,0.35,0.35);
	agk::PlaySprite(BIRD,14,1,1,14);
	x = agk::GetSpriteWidth(BIRD)/2;
//	agk::SetPhysicsDebugOn();
}// Main loop, called every frame

void app::Loop ( void )
{	
	switch (menuOption) {
	case 0:
		if (agk::GetTextHitTest(PLAY,agk::GetPointerX(),agk::GetPointerY()) && agk::GetPointerPressed() == 1){
			menuOption = 1;
			agk::DeleteText(PLAY);
		}


	break;
	case 1:
		agk::SetPhysicsGravity(0,500);
		for (int i = 0; i < 5; i++){
			BOX_X[i] -= 1;
			BOXT_X[i] -= 1;	
			agk::SetSpriteX(BOX[i],BOX_X[i]); 
			agk::SetSpriteX(BOXT[i],BOXT_X[i]); 
			if (BOX_X[i] < -48){
				BOX_X[i] = 754;
			}
			if (BOXT_X[i] < -48){
				BOXT_X[i] = 754;
			}

			if (agk::GetSpriteCollision(BOX[i],BIRD) == 1 || agk::GetSpriteCollision(BOXT[i],BIRD) == 1){
				agk::Print("Navin");
				if (!agk::GetSoundsPlaying(HIT)){
				agk::PlaySound(HIT);
				agk::SetSpriteAngle(BIRD,90);
				}
				menuOption = 0;
			}
			if (agk::GetSpriteX(BOX[i]) < agk::GetSpriteX(BIRD)){
				score += 1;
			}

		}
			agk::Print(score);

		for (int i = 0; i<2; i++){
			FOR_X[i] -= 1;
			agk::SetSpriteX(FOR[i],FOR_X[i]);
			if (FOR_X[i] < -640){
				FOR_X[i] = 640;
			}
		}

		if(agk::GetPointerPressed() == 1){
				APPLY_IMPULSE = 1;
				ballx = agk::GetSpriteX(BIRD);
				bally = agk::GetSpriteY(BIRD);
		}
		if (APPLY_IMPULSE== 1){
			agk::SetSpritePhysicsImpulse(BIRD,ballx + x,bally + x,0,-190000);
			agk::PlaySound(FLAP);
			APPLY_IMPULSE = 0;
		}
		break;
		
		default:
		break;
	}
	agk::Sync ( );
}
// Called when the app ends
void app::End ( void )
{

}

void Initialize(void){


}
void LoadResource(void){
	agk::LoadImage(BOX_IMG,"tree.png");
	agk::LoadImage(BOXT_IMG,"tree1.png");
	agk::LoadSound(FLAP,"flap.wav");
	agk::LoadSound(HIT,"splash.wav");
	agk::LoadImage(BIRD_IMG,"bird1.png");
	agk::LoadImage(FOR_IMG,"foreground.png");
	agk::LoadImage(BACK_IMG,"back1.png");

}
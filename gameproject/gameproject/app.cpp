/**
* Memo's Coins- Game project
* INTE 11223 – Programming Concepts
* Team Members:
* IM/2020/005 – Vishath Amarasinghe
* IM/2020/004 - Bimindu Aberathna
* IM/2020/034 - Abevarzene Sutharshon
* IM/2020/091 - Induwara Sahasraka
* IM/2020/044 - Shehan Chamudith
* 
* Requirments for run this game: SFML installed on computer and set it as an environment variable.

*/

#include<sfml/graphics.hpp>
#include<iostream>
#include<Windows.h>
#include<sstream>
#include <string>
#include<ctime>
#include<cassert>
#include<fstream>
using namespace sf;
using namespace std;



struct gameRunningParameter {
	int finalScore = 0;			//FInal Score of the player
	int GameLevel = 1;			//Game levels
	String playerInput = "";	//Player name container
	Text playerText;			//Player Name
	Font fonts;					//Used font
	int NavigationValue = 100;  //Windows Changing value
	bool finishingGame = false; //Game finishing Mode
	int FileWriteCount = 0;		//File Written Count
	int LevelEndBtnPosition = 0;//level end button
	bool jump = false;			//jump action Indicator
	int jump_value = 0;			//jump indicator
	double JumpDownValue = 0;	//falling down from grassland
	int coinCount = 0;			//total coin count in particular game level
	int ObstacleCount = 0;		//total obstacal count in particular game level
	int positionSize = 0;		// obstacal position
	int finishedStatus = 0;		//Coin finished status
	double x = 100, y = 500;	//doodle x ,y coordinates
	double dy = 0;				// speed in y axis
	double dx = 0;				//speed in x axis
	int value = 0;				//doodle walking side(Left/Right)
	int deleteVariable = 0;		//deleting variables
} ;


gameRunningParameter gameRunningParameters;

RenderWindow window(sf::VideoMode(1000, 570), "window");
Event ev;

//Textute Array(which contain all images)
Texture backgrond, boy, jumper, star, obstacle, LevelUp, startWindow, finishGame, InstructionPage,doodleRight;
Texture arr[10] = { backgrond,boy,jumper ,star,obstacle,LevelUp,startWindow,finishGame,InstructionPage,doodleRight };


//Sprite Array
Sprite backgrounds, boys, jumperS, starS, obstacleS, LevelUps, startWindowS, finishGameS, InstructionPageS,doodleRightS;
Sprite arr1[10] = { backgrounds, boys,jumperS,starS, obstacleS,LevelUps,startWindowS,finishGameS,InstructionPageS,doodleRightS };






/**
* Description: GrassLand positions(x and y coordinates)
*/
struct positions
{
	int x;
	int y;
};


/**
* Description: Obstacles positions(x and y coordinates)
*/
struct obstaclePositions
{
	int ObsX;
	int ObsY;
};


/**
* Description: Coin positions(x and y coordinates)
*/
struct coinArray
{
	int CoinX;
	int CoinY;
	int objectIdentify = 0;
};


/**
* Description: LevelUp button positions(x and y coordinates)
*/
struct  LevelUpImagePlacer
{
	int PlaceX;
	int PlaceY;
	int visibleContainer;
};


obstaclePositions* ObsPos;
positions* pos;
coinArray* CoinArrBuilt;
LevelUpImagePlacer* level1Image;





//Functions Used in this Game
void LoadingImages(Texture arr[], Sprite  arrS[]);
void jumpF();  //jump Function
void walkingF();  //Walking function
int obstacalCollision(obstaclePositions ObsPos[], RenderWindow& window);
void MakingObstacles(obstaclePositions obsArray[], Sprite arr1[], RenderWindow& window);
void coinMaker(coinArray ArrCoin[], Sprite arr1[], RenderWindow& window);


//Functions Used in this Game
void coinCollision(coinArray ArrCoin[]);
void changeLevel(RenderWindow& window, Sprite arr1[]);
void checkLevelFinished(LevelUpImagePlacer Level1Image[], RenderWindow& window, Sprite arr1[]);
void stairesSitting(positions posArray[]);
void CreateStairs(positions posArray[], Sprite arr1[], RenderWindow& window);



//Functions Used in this Game
void restartCurrentGame(int* restartState, RenderWindow& window, Sprite arr1[]);
void LevelEndingPoint(Sprite arr1[], RenderWindow& window, LevelUpImagePlacer Level1Image[]);
void LevelOne(RenderWindow& window, Sprite arr1[], coinArray CoinArrBuilt[],
	obstaclePositions ObsPos[], LevelUpImagePlacer Imageplacer[], positions* pos);



//Functions Used in this Game (Game Levels)
void Level1GameComponents(RenderWindow& window, Sprite arr1[]);
void Level2GameComponents(RenderWindow& window, Sprite arr1[]);
void Level3GameComponents(RenderWindow& window, Sprite arr1[]);
void Level4GameComponents(RenderWindow& window, Sprite arr1[]);
void Level5GameComponents(RenderWindow& window, Sprite arr1[]);
void deleteDynamics();

//Functions Used in this Game
void UserInputWindow(RenderWindow& window, Sprite arr1[], Event& ev);
void FinalScoreDisplay(RenderWindow& window);
void InstructionLoadingPage(RenderWindow& window, Sprite arr1[], Event& ev);
void WriteToFile(string name, int score);


/**
*Description: The LoadingImages() function will get image files and
check if thoses correctly loaded, if not it will show a error messege.
*@param arr[] is a Texture array containing all textures.
*@param arrS[] is a Sprite Array containing all Sprites.
*/
void LoadingImages(Texture arr[], Sprite  arrS[]) {
	try
	{
		arr[0].loadFromFile("GameImages/backgroundTrees.png");
		arrS[0].setTexture(arr[0]);
		arr[1].loadFromFile("GameImages/doodle.png");
		arrS[1].setTexture(arr[1]);
		arrS[1].setScale(1, 1);
		arr[2].loadFromFile("GameImages/grassLand.png");
		arrS[2].setTexture(arr[2]);
		arrS[2].setPosition(400, 450);
		arr[3].loadFromFile("GameImages/Star1.png");
		arrS[3].setTexture(arr[3]);
		arrS[3].setPosition(400, 400);
		arrS[3].scale(1, 1);
		arr[4].loadFromFile("GameImages/obstacle.png");
		arrS[4].setTexture(arr[4]);
		arrS[4].setPosition(250, 400);
		arr[5].loadFromFile("GameImages/LevelUp.png");
		arrS[5].setTexture(arr[5]);
		arr[6].loadFromFile("GameImages/startBack.png");
		arrS[6].setTexture(arr[6]);
		arr[7].loadFromFile("GameImages/finishGame.png");
		arrS[7].setTexture(arr[7]);
		arr[8].loadFromFile("GameImages/introductions.png");
		arrS[8].setTexture(arr[8]);
		arr[9].loadFromFile("GameImages/doodleRight.png");
		arrS[9].setTexture(arr[9]);
	}
	catch (const std::exception&)
	{
		cout << "Image Loading Error";
		window.close();
	}
}


/**
* Description: this function create the jump animation
*/
void jumpF() {
	if (gameRunningParameters.jump) {  //check jump is ok.

		gameRunningParameters.dy += 0.4;
		gameRunningParameters.y += gameRunningParameters.dy;
		if (gameRunningParameters.y > 500)
		{
			gameRunningParameters.dy = -10.0;
			gameRunningParameters.jump = false;
		}
	}
}

/**
* Description: walkingF function change the x corrdinate and Y coordinate then he animated as walking.
*/
void walkingF() {
	if (gameRunningParameters.value == 0) {
		gameRunningParameters.x = gameRunningParameters.x + 5;
		if (gameRunningParameters.x >= 900) { //walking to riight direction 
			gameRunningParameters.value = 1;
		}
	}
	else {
		gameRunningParameters.value = 1;
		gameRunningParameters.x = gameRunningParameters.x - 5; //walking to left direction
		if (gameRunningParameters.x <= 0) {
			gameRunningParameters.value = 0;
		}
	}	
}

/**
* Description: obstacalCollision function check if the doodle make a collision with ground obstacles
* if doodle hit with ground obstacles function will return a value 1
* @param ObsPos[] is the obstacle array
*/
int obstacalCollision(obstaclePositions ObsPos[],RenderWindow &window) {
	int returnState = 0;
	for (int i = 0; i < gameRunningParameters.ObstacleCount; i++)
	{
		//check doodle is inside the area of obstacle.
		if ((gameRunningParameters.x)+30 >= (ObsPos[i].ObsX) && ((gameRunningParameters.x)+30) <= (ObsPos[i].ObsX + 85) && ((gameRunningParameters.y)+30) <= (ObsPos[i].ObsY + 10) && ((gameRunningParameters.y) + 30) >= (ObsPos[i].ObsY - 40))
		{
			cout << "game Over" << endl;
			returnState = 1;
		}
	}
	return returnState;
}


/**
* Description: MakingObstacles function render the obstacles in the obsArray.
* @param obsArray[] is the obstacle array.
* @param arr1[] array is the sprite array(which contains image texturess)
*/

void MakingObstacles(obstaclePositions obsArray[], Sprite arr1[],RenderWindow &window) {
	for (int i = 0; i < 2; i++)
	{
		arr1[4].setPosition(obsArray[i].ObsX, obsArray[i].ObsY);
		window.draw(arr1[4]); //Drawing obstacles
	}
}


/**
* description: coinMaker function render coins in coinArray
* @param arrCoin[] is the coin Array.
* @param image array
*/
void coinMaker(coinArray ArrCoin[],Sprite arr1[], RenderWindow& window) {
	for (int i = 0; i < gameRunningParameters.coinCount; i++)
	{
		if (ArrCoin[i].objectIdentify!=1)  // check if the coin is taken from doodle or not(coin Collion with doodle)
		{
			arr1[3].setPosition(ArrCoin[i].CoinX, ArrCoin[i].CoinY);
			window.draw(arr1[3]); //draw coins
		}
	}
}


/**
* description: CoinCollision fucntion check if the doodle make collison with coin. if so, coin will dissapeared.
* @param coin Array
*/
void coinCollision(coinArray ArrCoin[]) {
	for (int i = 0; i < gameRunningParameters.coinCount; i++)
	{
		//checking whether doodle is in the coin's area or not
		if (gameRunningParameters.x >= (ArrCoin[i].CoinX-13) && gameRunningParameters.x <= (ArrCoin[i].CoinX + 33) && gameRunningParameters.y <= (ArrCoin[i].CoinY+13) && gameRunningParameters.y >= (ArrCoin[i].CoinY - 33))
		{
			if (ArrCoin[i].objectIdentify==0)
			{
				ArrCoin[i].objectIdentify = 1; //make coins dissapearing from the Game
				gameRunningParameters.finishedStatus = gameRunningParameters.finishedStatus + 1;
			}
			
		}
	}
}


/**
* description: changeLevel() function will change the game level state.
* @param arr1 is the image array
*/
void changeLevel(RenderWindow& window, Sprite arr1[]) {
	cout << gameRunningParameters.GameLevel << endl;
	if (gameRunningParameters.GameLevel == 2)
	{
		//change the Game level to level 2 and Create Level 2 Components.
		Level2GameComponents(window, arr1);
	}
	else if (gameRunningParameters.GameLevel ==1)
	{
		//change the Game level to level 2 and Create Level 2 Components.
		Level1GameComponents(window, arr1);
	}
	else if (gameRunningParameters.GameLevel == 3) {
		//change the Game level to level 2 and Create Level 2 Components.
		Level3GameComponents(window, arr1);
	}
	else if (gameRunningParameters.GameLevel ==4)
	{
		Level4GameComponents(window, arr1);
	}
	else if (gameRunningParameters.GameLevel == 5)
	{
		Level5GameComponents(window, arr1);
	}
	else {
		gameRunningParameters.finishingGame = true;
	}
}


/**
* description: checLevelFinished() function check whether doodle is inside the area of level change button.
* @param Level1Image[] array has level change button and its possition.
* @param arr1 is the image array
*/
void checkLevelFinished(LevelUpImagePlacer Level1Image[],RenderWindow &window,Sprite arr1[]) {
	
	if ((gameRunningParameters.x + 30) >= Level1Image[0].PlaceX && (gameRunningParameters.x + 30) <= Level1Image[0].PlaceX + 82 && (gameRunningParameters.y + 30) >= Level1Image[0].PlaceY && (gameRunningParameters.y + 30) <= Level1Image[0].PlaceY + 60)
		{
			cout << "levelPassed" << endl;
			if (Level1Image[0].visibleContainer==0 && (gameRunningParameters.coinCount == gameRunningParameters.finishedStatus)) //check whether the game level btn is visible or not
				//and default coin count is equal to coinCount.
			{
				cout << "level Passed ANd Entered" << endl;
				gameRunningParameters.GameLevel = gameRunningParameters.GameLevel + 1;
				Level1Image[0].visibleContainer = 1;
				gameRunningParameters.finalScore = gameRunningParameters.finalScore + (gameRunningParameters.coinCount) * 5; //Calculating the players final Score
				cout << "final Count " << gameRunningParameters.finalScore << endl;
				changeLevel( window, arr1);
			}
		}
}



/**
* description: stairesSitting() function will check whether the doodle is on the grassLand.
* @param posArray is an array which is containing positions of the GrassLands.
* @param positionSize is an array size of posArray.
*/
void stairesSitting(positions posArray[]) {

	for (int i = 0; i < gameRunningParameters.positionSize; i++)
	{
		if (((gameRunningParameters.x+30)) >= posArray[i].x && ((gameRunningParameters.x +30)) <= (posArray[i].x+145) && ((gameRunningParameters.y)) <= posArray[i].y+20 && gameRunningParameters.y >= posArray[i].y-48)
		{
			//check doodle is inside the area of GrassLands
			gameRunningParameters.y = (posArray[i].y) - 48;
			gameRunningParameters.dy = -10;
			gameRunningParameters.jump = false; // stop doodles jump.
			gameRunningParameters.JumpDownValue = 0;
		}
		else if (gameRunningParameters.y < 500 && gameRunningParameters.y>0 && gameRunningParameters.jump == false) // if doodle is not in the area of GrassLand, then fall down to the groundFloor.
		{
			gameRunningParameters.JumpDownValue = gameRunningParameters.JumpDownValue + 0.5;
			gameRunningParameters.y = gameRunningParameters.y + gameRunningParameters.JumpDownValue;
		}
	}
}


/**
* Description: CreateStairs() function will create GrassLand Stairs.
* @param posArray[] is the array which contains positions of GrassLands.
*/
void CreateStairs(positions posArray[], Sprite arr1[],RenderWindow &window) {
	for (int i = 0; i < gameRunningParameters.positionSize; i++)
	{
		arr1[2].setPosition(posArray[i].x, posArray[i].y);
		window.draw(arr1[2]);
	}
}


/**
* Descripton: restartCurrentGame() function start the current Game Level again if doodle crash with obstacles.
* @param restartState is the return value of obstacleCollion function which indicates the collision between obstacles.
*/
void restartCurrentGame(int * restartState,RenderWindow &window,Sprite arr1[]) {
	if (*restartState==1)
	{
		Clock clock;
		
		clock.restart();

		for (;  clock.getElapsedTime().asSeconds()<=0.7;)  //sleep the game 0.5 seconds
		{
			Text text;
			Font font;
			
			font.loadFromFile("Fonts/Liquidie.ttf");
			text.setFont(font);
			text.setPosition(280, 200);
			text.setString("Game Over");  //Drawing Game Over Text 
			text.setCharacterSize(150);

			Text restartLevelText;
			restartLevelText.setFont(font);
			restartLevelText.setCharacterSize(25);
			string restartTextMaker = "Restarting Game Level " + to_string(gameRunningParameters.GameLevel);
			restartLevelText.setString(restartTextMaker); //Drawing Restarting Game State
			restartLevelText.setPosition(420, 500);

			window.clear();
			window.draw(restartLevelText);
			window.draw(text);
			window.display();
		}
		changeLevel(window, arr1); //Repeating the same Level
	}
}


/**
* Description: LevelEndingPoint() function check if the doodle collect all coins. 
* if doodle collect all coins then  appear the level ending button
* @param level1Image image of level up image
*/
void LevelEndingPoint(Sprite arr1[],RenderWindow &window, LevelUpImagePlacer Level1Image[]) {
	gameRunningParameters.LevelEndBtnPosition = gameRunningParameters.GameLevel - 1;
	if (gameRunningParameters.finishedStatus==(gameRunningParameters.coinCount) && Level1Image[0].visibleContainer == 0)
	{
		arr1[5].setPosition(Level1Image[0].PlaceX, Level1Image[0].PlaceY); //Draw the LevelUp button.
		window.draw(arr1[5]);
	}
}

/**
* Description: LevelOne() function start the initial Game.
* All other functions are  inside this function.
*/
void LevelOne(RenderWindow& window, Sprite arr1[],coinArray CoinArrBuilt[],obstaclePositions ObsPos[],LevelUpImagePlacer Imageplacer[],positions *pos) {


	walkingF(); //walking function 
	jumpF();    //jumping function

	window.clear(Color::Blue);
	window.draw(arr1[0]);

	if (gameRunningParameters.value==0)
	{
		arr1[9].setPosition(gameRunningParameters.x, gameRunningParameters.y);
		window.draw(arr1[9]); //rotate doodle 
	}
	else {
		arr1[1].setPosition(gameRunningParameters.x, gameRunningParameters.y);
		window.draw(arr1[1]);  //rotate doodle 
	}

	

	
	

	FinalScoreDisplay(window);  //final Score display function
	coinMaker(CoinArrBuilt, arr1, window);   //make related coins according to game level
	MakingObstacles(ObsPos, arr1, window);	//create obstacles according to game level
	CreateStairs(&(*pos), arr1, window);	//create grassLands accrding to game level
	stairesSitting(&(*pos));				//manage state of standing on grassland
	int ObstacleCollisionReturn = obstacalCollision(ObsPos, window);  //trigger obstacal collision
	restartCurrentGame(&ObstacleCollisionReturn, window,arr1);        //restart current game level
	coinCollision(CoinArrBuilt);									  //trigger coin collison
	LevelEndingPoint(arr1,window,Imageplacer);
	checkLevelFinished(Imageplacer, window, arr1);					  //check finished game levels
	window.display();
}







/**
* Description: Levvel1 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level1GameComponents(RenderWindow &window,Sprite arr1[]) {

	gameRunningParameters.x = 100;
	gameRunningParameters.y = 510;
	gameRunningParameters.finishedStatus=0;
	ObsPos = new obstaclePositions[2];
	ObsPos[0].ObsX = 500;
	ObsPos[0].ObsY = 540;
	ObsPos[1].ObsX = 570;
	ObsPos[1].ObsY = 540;

	gameRunningParameters.ObstacleCount = 2;

	pos = new positions[1];
	pos[0].x = 400;
	pos[0].y = 450;

	

	CoinArrBuilt =new coinArray[1];
	CoinArrBuilt[0].CoinX = 555;
	CoinArrBuilt[0].CoinY = 420;
	CoinArrBuilt[0].objectIdentify = 0;

	gameRunningParameters.coinCount = 1;


	level1Image =new LevelUpImagePlacer[1];
	level1Image[0].PlaceX = 100;
	level1Image[0].PlaceY = 380;
	level1Image[0].visibleContainer = 0;

}

/**
* Description: Level 2 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level4GameComponents(RenderWindow& window, Sprite arr1[]) {

	deleteDynamics();

	gameRunningParameters.x = 100;
	gameRunningParameters.y = 510;
	gameRunningParameters.finishedStatus = 0;


	gameRunningParameters.ObstacleCount = 2;
	ObsPos= new obstaclePositions[gameRunningParameters.ObstacleCount];   //obstacle Array
	ObsPos[0].ObsX = 250;
	ObsPos[0].ObsY = 540;
	ObsPos[1].ObsX = 550;
	ObsPos[1].ObsY = 540;


	gameRunningParameters.positionSize = 1;
	pos = new positions[gameRunningParameters.positionSize];     //GrassLand Array
	pos[0].x = 800;
	pos[0].y = 450;


	gameRunningParameters.coinCount = 2;
	CoinArrBuilt = new coinArray[gameRunningParameters.coinCount];  //Coin Array
	CoinArrBuilt[0].CoinX = 320;
	CoinArrBuilt[0].CoinY = 420;
	CoinArrBuilt[0].objectIdentify = 0;

	CoinArrBuilt[1].CoinX = 820;
	CoinArrBuilt[1].CoinY = 400;
	CoinArrBuilt[1].objectIdentify = 0;
	


	level1Image = new LevelUpImagePlacer[1];  //LevelUp Button Array
	level1Image[0].PlaceX = 100;
	level1Image[0].PlaceY = 450;
	level1Image[0].visibleContainer = 0;
}



/**
* Description: Level3 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level3GameComponents(RenderWindow& window, Sprite arr1[]) {

	deleteDynamics();

	gameRunningParameters.finishedStatus = 0;
	gameRunningParameters.x = 100;   //Default x and Y coordinates
	gameRunningParameters.y = 510;


	gameRunningParameters.ObstacleCount = 2;
	ObsPos = new obstaclePositions[gameRunningParameters.ObstacleCount];   //obstacle Array
	ObsPos[0].ObsX = 400;
	ObsPos[0].ObsY = 540;
	ObsPos[1].ObsX = 650;
	ObsPos[1].ObsY = 540;

	

	gameRunningParameters.positionSize = 1;
	pos= new positions[gameRunningParameters.positionSize];   //GrassLand Array
	pos[0].x = 00;
	pos[0].y = 490;


	CoinArrBuilt = new coinArray[2];   //Coin Array
	CoinArrBuilt[0].CoinX = 555;
	CoinArrBuilt[0].CoinY = 420;
	CoinArrBuilt[0].objectIdentify = 0;

	CoinArrBuilt[1].CoinX = 300;
	CoinArrBuilt[1].CoinY = 420;
	CoinArrBuilt[1].objectIdentify = 0;
	gameRunningParameters.coinCount = 2;

	level1Image= new LevelUpImagePlacer[1];   //LevelUp Button Array
	level1Image[0].PlaceX = 100;
	level1Image[0].PlaceY = 450;
	level1Image[0].visibleContainer = 0;
}


/**
* Description: Level2 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level2GameComponents(RenderWindow& window, Sprite arr1[]) {

	deleteDynamics();

	gameRunningParameters.finishedStatus = 0;
	gameRunningParameters.x = 100;   //Default x and Y coordinates
	gameRunningParameters.y = 510;


	gameRunningParameters.ObstacleCount = 1;
	ObsPos = new obstaclePositions[gameRunningParameters.ObstacleCount];   //obstacle Array
	ObsPos[0].ObsX = 250;
	ObsPos[0].ObsY = 540;


	gameRunningParameters.positionSize = 1;
	pos= new positions[gameRunningParameters.positionSize];   //GrassLand Array
	pos[0].x = 720;
	pos[0].y = 450;


	gameRunningParameters.coinCount = 2;
	CoinArrBuilt= new coinArray[gameRunningParameters.coinCount];   //Coin Array
	CoinArrBuilt[0].CoinX = 265;
	CoinArrBuilt[0].CoinY = 420;
	CoinArrBuilt[0].objectIdentify = 0;

	CoinArrBuilt[1].CoinX = 680;
	CoinArrBuilt[1].CoinY = 350;
	CoinArrBuilt[1].objectIdentify = 0;


	level1Image = new LevelUpImagePlacer[1];   //LevelUp Button Array
	level1Image[0].PlaceX = 100;
	level1Image[0].PlaceY = 450;
	level1Image[0].visibleContainer = 0;
}


/**
* Description: Level 2 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level5GameComponents(RenderWindow& window, Sprite arr1[]) {

	deleteDynamics();

	gameRunningParameters.finishedStatus = 0;
	gameRunningParameters.x = 100;   //Default x and Y coordinates
	gameRunningParameters.y = 510;


	gameRunningParameters.ObstacleCount = 3;
	ObsPos = new obstaclePositions[gameRunningParameters.ObstacleCount];   //obstacle Array
	ObsPos[0].ObsX = 400;
	ObsPos[0].ObsY = 540;
	ObsPos[1].ObsX = 520;
	ObsPos[1].ObsY = 540;
	ObsPos[2].ObsX = 650;
	ObsPos[2].ObsY = 540;



	gameRunningParameters.positionSize = 2;
	pos = new positions[gameRunningParameters.positionSize];     //GrassLand Array
	pos[0].x = 280;
	pos[0].y = 450;
	pos[1].x = 580;
	pos[1].y = 450;


	gameRunningParameters.coinCount = 2;
	CoinArrBuilt = new coinArray[gameRunningParameters.coinCount];  //Coin Array
	CoinArrBuilt[0].CoinX = 340;
	CoinArrBuilt[0].CoinY = 350;
	CoinArrBuilt[0].objectIdentify = 0;

	CoinArrBuilt[1].CoinX = 500;
	CoinArrBuilt[1].CoinY = 350;
	CoinArrBuilt[1].objectIdentify = 0;


	level1Image = new LevelUpImagePlacer[1];  //LevelUp Button Array
	level1Image[0].PlaceX = 100;
	level1Image[0].PlaceY = 450;
	level1Image[0].visibleContainer = 0;
}


/**
* Description: UserInputWindow() take players name as an input
*/
void UserInputWindow(RenderWindow &window,Sprite arr1[],Event &ev) {
	window.clear();
	window.draw(arr1[6]);
	gameRunningParameters.fonts.loadFromFile("Fonts/Poppins.ttf");
	gameRunningParameters.playerText.setFont(gameRunningParameters.fonts);
	gameRunningParameters.playerText.setCharacterSize(35);
	window.setFramerateLimit(11);
	string val = "";

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		gameRunningParameters.NavigationValue=1010;
		window.setFramerateLimit(60);
	}
	
	
	if (ev.type==Event::TextEntered)
	{
		if (isprint(ev.text.unicode))
		{
			gameRunningParameters.playerInput = gameRunningParameters.playerInput + (String)ev.text.unicode;
			val = (String)ev.text.unicode;
		}
		gameRunningParameters.playerText.setString(gameRunningParameters.playerInput);
		cout << val << endl;
		gameRunningParameters.playerText.setPosition(250,370);
		
	}
	
	window.draw(gameRunningParameters.playerText);
	window.display();
}

/**
* Description: InstructionLoadingPage() shows the instructions of this Game
*/
void InstructionLoadingPage(RenderWindow& window, Sprite arr1[]) {
	window.setFramerateLimit(11);
	window.clear();
	window.draw(arr1[8]);
	window.display();
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		gameRunningParameters.NavigationValue = 1020;
		window.setFramerateLimit(60);  //Change Frame Rate
	}
}


/**
* Description: FinalScoreDisplay() function shows the score gaind by the player
*/
void FinalScoreDisplay(RenderWindow &window) {
	Text scoreText;
	Text levelDisplay;
	Font ScoreFont;
	ScoreFont.loadFromFile("Fonts/Liquidie.ttf");
	scoreText.setFont(ScoreFont);
	levelDisplay.setFont(ScoreFont);
	scoreText.setCharacterSize(35);
	levelDisplay.setCharacterSize(35);
	string printedScore = "Score:  " +to_string(gameRunningParameters.finalScore);
	string printLevelDisplay = "Level: " + to_string(gameRunningParameters.GameLevel);
	scoreText.setString(printedScore);
	levelDisplay.setString(printLevelDisplay);
	scoreText.setPosition(30, 5);
	levelDisplay.setPosition(30,34);
	window.draw(scoreText);
	window.draw(levelDisplay);
}

/**
* Description: Write Player name and score into a text file
* @param name is the player name
* @param score is the score that player gained
*/
void WriteToFile(string name, int score) {
	#pragma warning(disable:4996)

	// Write to the file

	ifstream myfile;
	myfile.open("results.txt");
	if (myfile) {
		ofstream MyFile("results.txt", ios::app);
		MyFile << "Name : " << name;
		MyFile << "\nScore : " << score;
		MyFile << "\n\n ";
		MyFile.close();
	}
	else {
		ofstream MyFile("results.txt");
		MyFile << "Name : " << name;
		MyFile << "\nScore : " << score;
		MyFile << "\n\n ";
		MyFile.close();

	}
}

/**
* Description: delete dynamic memory locations
*/
void deleteDynamics() {
	delete []ObsPos;
	delete []pos;
	delete []CoinArrBuilt;
	delete []level1Image;

}



/**
* full program runs from here
*/
int main() {
	

	window.setFramerateLimit(60);

	Level1GameComponents(window, arr1); //load Level1 Components
	LoadingImages(arr, arr1); //loading Images 
	arr1[1].setPosition(gameRunningParameters.x, gameRunningParameters.y);
	
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	while (window.isOpen())
		{
			while (window.pollEvent(ev))
			{
				if (ev.type == sf::Event::Closed) {//check if the player close the window
					deleteDynamics();
					window.close();
					cout << "closed" << endl;
				}
			}
			if (gameRunningParameters.NavigationValue == 100) //Navigating to User Name input 
			{
				UserInputWindow(window, arr1,ev); //user Name input function

			}
			else {
				if (gameRunningParameters.finishingGame)  //finishing the game 
				{
					window.clear();
					window.draw(arr1[7]);
					window.display();
					if (gameRunningParameters.FileWriteCount==0)
					{
						WriteToFile(gameRunningParameters.playerInput, gameRunningParameters.finalScore);//Writing to the file
						gameRunningParameters.FileWriteCount += 1;
					}
					
				}
				else if (gameRunningParameters.NavigationValue==1010)
				{
					InstructionLoadingPage(window, arr1);  //load Instruction Page
				}
				else 
				{
					if (ev.type == Event::MouseButtonPressed)
					{
						if (ev.mouseButton.button == Mouse::Left) {//start jumping
							gameRunningParameters.jump = true;
							gameRunningParameters.jump_value = 0;
						}
					}

					
					//Game levels start from here.
					LevelOne(window,arr1,CoinArrBuilt,ObsPos,level1Image,pos);
				}
				
			}
		}
	
	return 0;
}



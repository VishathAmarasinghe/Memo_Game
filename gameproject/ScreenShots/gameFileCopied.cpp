/**
* Memo's Coins- Game project
* INTE 11223 – Programming Concepts
* Team Members:
* IM/2020/005 – Vishath Amarasinghe
* IM/2020/004 - Bimindu Aberathna
* IM/2020/034 - Abevarzene Sutharshon
* IM/2020/091 - Induwara Sahasraka
* IM/2020/044 - Shehan Chamudith

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



int finalScore = 0; //Final Score of the player
int GameLevel = 1;  //Game Level
String playerInput = "";  //Player Name
Text playerText;
Font fonts;
int NavigationValue = 100;  //Changing windows 
bool finishingGame = false; //Game Finish State
int FileWriteCount = 0; //File written Count

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

//functions Used in this Game 
void Level2GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level1GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level3GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void FinalScoreDisplay(RenderWindow& window);
void LoadingImages(Texture arr[], Sprite  arrS[]);



//Functions Used in this Game
void jumpF(bool* jump, double* dy, double* y);
void walkingF(int* value, double* x);
int obstacalCollision(double* x, double* y, obstaclePositions ObsPos[], int* ObstacleCount, RenderWindow& window);
void MakingObstacles(obstaclePositions obsArray[], Sprite arr1[], RenderWindow& window);
void coinMaker(coinArray ArrCoin[], Sprite arr1[], RenderWindow& window, int* coinCount);


//Functions Used in this Game
void coinCollision(double* x, double* y, coinArray ArrCoin[], int* coinCount, int* finishedStatus);
void changeLevel(int* GameLevel, RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void checkLevelFinished(double* x, double* y, LevelUpImagePlacer Level1Image[], RenderWindow& window, Sprite arr1[], int* GameLevel, int* coinCount, int* ObstacleCount, int* finishedStatus, int* positionSize);
void stairesSitting(double* x, double* y, double* dy, bool* jump, int* JumpDownValue, positions posArray[], int* positionSize);
void CreateStairs(positions posArray[], int* size, Sprite arr1[], RenderWindow& window);



//Functions Used in this Game
void restartCurrentGame(int* restartState, RenderWindow& window, Sprite arr1[], double* x, double* y, int* GameLevel, int* coinCount, int* ObstacleCount, int* positionSize);
void LevelEndingPoint(int* finishedStatus, int* coinCount, Sprite arr1[], RenderWindow& window, int* LevelNo, LevelUpImagePlacer Level1Image[], int* LevelEndBtnPosition);
void LevelOne(double* x, double* y, int* value, bool* jump, double* dy, RenderWindow& window, Sprite arr1[], int* finishedStatus, coinArray CoinArrBuilt[],
	obstaclePositions ObsPos[], LevelUpImagePlacer Imageplacer[], int* levelendBTN, int* GameLevel, int* coinCount, int* ObstacleCount, positions* pos, int* positionSize, int* JumpDownValue);



//Functions Used in this Game (Game Levels)
void Level1GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level2GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level3GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level4GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);
void Level5GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize);


//Functions Used in this Game
void UserInputWindow(RenderWindow& window, Sprite arr1[], Event& ev);
void FinalScoreDisplay(RenderWindow& window);
void InstructionPage(RenderWindow& window, Sprite arr1[], Event& ev);
void WriteToFile(string name, int score);


/**
*Description: The LoadingImages() function will get image files and
check if thoses correctly loaded, if not it will show a error messege.
*@param arr[] is a Texture array containing all textures.
*@param arrS[] is a Sprite Array containing all Sprites.
*/
void LoadingImages(Texture arr[], Sprite  arrS[]) {
	if ((!arr[0].loadFromFile("backgroundTrees.png")))
	{
		cout << "Game Background Image Loading Error Occurred" << endl;
	}
	else {
		arrS[0].setTexture(arr[0]);
	}
	if ((!arr[1].loadFromFile("doodle.png")))
	{
		cout << "Game doodle Image Loading Error Occurred" << endl;
	}
	else {
		arrS[1].setTexture(arr[1]);
		arrS[1].setScale(1, 1);
	}
	if (!arr[2].loadFromFile("grassLand.png"))
	{
		cout << "Game GrassLands Image Loading Error Occurred" << endl;
	}
	else {
		arrS[2].setTexture(arr[2]);
		arrS[2].setPosition(400, 450);
	}
	if (!arr[3].loadFromFile("Star1.png"))
	{
		cout << "Game Coin Image Loading Error Occurred" << endl;
	}
	else {
		arrS[3].setTexture(arr[3]);
		arrS[3].setPosition(400, 400);
		arrS[3].scale(1, 1);
	}
	if (!arr[4].loadFromFile("obstacle.png"))
	{
		cout << "Game Ground Obstacles Image Loading Error Occurred" << endl;
	}
	else {
		arrS[4].setTexture(arr[4]);
		arrS[4].setPosition(250, 400);
	}
	if (!arr[5].loadFromFile("LevelUp.png"))
	{
		cout << "Game LevelUp Image Loading Error Occurred" << endl;
	}
	else {
		arrS[5].setTexture(arr[5]);
	}
	if (!arr[6].loadFromFile("startBack.png"))
	{
		cout << "Game welcome Page Image Loading Error Occurred" << endl;
	}
	else {
		arrS[6].setTexture(arr[6]);
	}
	if (!arr[7].loadFromFile("finishGame.png"))
	{
		cout << "Game Finising Image Loading Error Occurred" << endl;
	}
	else {
		arrS[7].setTexture(arr[7]);
	}
	if (!arr[8].loadFromFile("introductions.png"))
	{
		cout << "Game Instructions Image Loading Error Occurred" << endl;
	}
	else {
		arrS[8].setTexture(arr[8]);
	}
}


/**
* Description: this function create the jump animation
* @param jump gives the signal to proceed the jump function.
* @param dy gives
* @param y gives the doodles y coordinate.
*/
void jumpF(bool* jump, double* dy, double* y) {
	if (*jump) {

		*dy += 0.4;
		*y += *dy;
		if (*y > 500)
		{
			*dy = -10.0;
			*jump = false;
		}
	}
}

/**
* Description: walkingF function change the x corrdinate and Y coordinate then he animated as walking.
* @param x gives the x coordinate.
* @param value indicates if doodle is in any corner.
*/
void walkingF(int* value, double* x) {
	if (*value == 0) {
		*x = *x + 5;
		if (*x >= 900) { //walking to left direction 
			*value = 1;
		}
	}
	else {
		*value = 1;
		*x = *x - 5; //walking to right direction
		if (*x <= 0) {
			*value = 0;
		}
	}
}

/**
* Description: obstacalCollision function check if the doodle make a collision with ground obstacles
* if doodle hit with ground obstacles function will return a value 1
* @param x,y shows current coordinates of the doodle.
* @param ObsPos[] is the obstacle array
* @param ObstacleCount is the number of elements in the array.
*/
int obstacalCollision(double* x, double* y, obstaclePositions ObsPos[], int* ObstacleCount, RenderWindow& window) {
	int returnState = 0;
	for (int i = 0; i < *ObstacleCount; i++)
	{
		//check doodle is inside the area of obstacle.
		if ((*x) + 30 >= (ObsPos[i].ObsX) && ((*x) + 30) <= (ObsPos[i].ObsX + 85) && ((*y) + 30) <= (ObsPos[i].ObsY + 10) && 
			((*y) + 30) >= (ObsPos[i].ObsY - 40))
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

void MakingObstacles(obstaclePositions obsArray[], Sprite arr1[], RenderWindow& window) {
	for (int i = 0; i < 2; i++)
	{
		arr1[4].setPosition(obsArray[i].ObsX, obsArray[i].ObsY);
		window.draw(arr1[4]); //Drawing obstacles
	}
}


/**
* description: coinMaker function render coins in coinArray
* @param arrCoin[] is the coin Array.
* @param coinCount is the size of the Array
*/
void coinMaker(coinArray ArrCoin[], Sprite arr1[], RenderWindow& window, int* coinCount) {
	for (int i = 0; i < *coinCount; i++)
	{
		if (ArrCoin[i].objectIdentify != 1)  // check if the coin is taken from doodle or not(coin Collion with doodle)
		{
			arr1[3].setPosition(ArrCoin[i].CoinX, ArrCoin[i].CoinY);
			window.draw(arr1[3]); //draw coins
		}
	}
}


/**
* description: CoinCollision fucntion check if the doodle make collison with coin. if so, coin will dissapeared.
* @param x,y coordinated of the doodle.
* @param ArrCoin is the coin Array.
* @param coinCount is the size of the coinArray.
*/
void coinCollision(double* x, double* y, coinArray ArrCoin[], int* coinCount, int* finishedStatus) {
	for (int i = 0; i < *coinCount; i++)
	{
		//checking whether doodle is in the coin's area or not
		if (*x >= (ArrCoin[i].CoinX - 10) && *x <= (ArrCoin[i].CoinX + 30) && *y <= (ArrCoin[i].CoinY + 10) && *y >= (ArrCoin[i].CoinY - 30))
		{
			if (ArrCoin[i].objectIdentify == 0)
			{
				ArrCoin[i].objectIdentify = 1; //make coins dissapearing from the Game
				*finishedStatus = *finishedStatus + 1;
				cout << "Coin Collision" << endl;
			}

		}
	}
}


/**
* description: changeLevel() function will change the game level state.
* @param GameLevel shows the current Game Level
*/
void changeLevel(int* GameLevel, RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {
	cout << *GameLevel << endl;
	if (*GameLevel == 2)
	{
		//change the Game level to level 2 and Create Level 2 Components.
		Level2GameComponents(window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
	}
	else if (*GameLevel == 1)
	{
		//change the Game level to level 2 and Create Level 2 Components.
		Level1GameComponents(window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
	}
	else if (*GameLevel == 3) {
		//change the Game level to level 2 and Create Level 2 Components.
		Level3GameComponents(window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
	}
	else if (*GameLevel == 4)
	{
		Level4GameComponents(window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
	}
	else if (*GameLevel == 5)
	{
		Level5GameComponents(window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
	}
	else {
		finishingGame = true;
	}
}


/**
* description: checLevelFinished() function check whether doodle is inside the area of level change button.
* @param Level1Image[] array has level change button and its possition.
*/
void checkLevelFinished(double* x, double* y, LevelUpImagePlacer Level1Image[], RenderWindow& window, Sprite arr1[], 
	int* GameLevel, int* coinCount, int* ObstacleCount, int* finishedStatus, int* positionSize) {

	if ((*x + 30) >= Level1Image[0].PlaceX && (*x + 30) <= Level1Image[0].PlaceX + 82 && 
		(*y + 30) >= Level1Image[0].PlaceY && (*y + 30) <= Level1Image[0].PlaceY + 60)
	{
		cout << "levelPassed" << endl;
		if (Level1Image[0].visibleContainer == 0 && (*coinCount == *finishedStatus)) //check whether the game level btn is visible or not
			//and default coin count is equal to coinCount.
		{
			cout << "level Passed ANd Entered" << endl;
			*GameLevel = *GameLevel + 1;
			Level1Image[0].visibleContainer = 1;
			finalScore = finalScore + (*coinCount) * 5; //Calculating the players final Score
			cout << "final Count " << finalScore << endl;
			changeLevel(&(*GameLevel), window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize));
			cout << "Level Changed" << endl;
		}
	}
}



/**
* description: stairesSitting() function will check whether the doodle is on the grassLand.
* @param posArray is an array which is containing positions of the GrassLands.
* @param positionSize is an array size of posArray.
*/
void stairesSitting(double* x, double* y, double* dy, bool* jump, int* JumpDownValue, positions posArray[], int* positionSize) {

	for (int i = 0; i < *positionSize; i++)
	{
		if (((*x + 30)) >= posArray[i].x && ((*x + 30)) <= (posArray[i].x + 145) && ((*y)) <= posArray[i].y + 33 && *y >= posArray[i].y - 33)
		{
			//check doodle is inside the area of GrassLands
			*dy = -10;
			*jump = false; // stop doodles jump.
			*JumpDownValue = 0;
			cout << "jumped Up" << endl;
		}
		else if (*y < 500 && *y>0 && *jump == false) // if doodle is not in the area of GrassLand, then fall down to the groundFloor.
		{
			*JumpDownValue = *JumpDownValue + 1;
			*y = *y + *JumpDownValue;
		}
	}
}


/**
* Description: CreateStairs() function will create GrassLand Stairs.
* @param posArray[] is the array which contains positions of GrassLands.
*/
void CreateStairs(positions posArray[], int* size, Sprite arr1[], RenderWindow& window) {
	for (int i = 0; i < *size; i++)
	{
		arr1[2].setPosition(posArray[i].x, posArray[i].y);
		window.draw(arr1[2]);
	}
}


/**
* Descripton: restartCurrentGame() function start the current Game Level again if doodle crash with obstacles.
* @param restartState is the return value of obstacleCollion function which indicates the collision between obstacles.
*/
void restartCurrentGame(int* restartState, RenderWindow& window, Sprite arr1[], double* x, double* y, int* GameLevel, int* coinCount, int* ObstacleCount, int* positionSize) {
	if (*restartState == 1)
	{
		Clock clock;

		clock.restart();

		for (; clock.getElapsedTime().asSeconds() <= 0.7;)  //sleep the game 0.5 seconds
		{
			Text text;
			Font font;

			font.loadFromFile("Liquidie.ttf");
			text.setFont(font);
			text.setPosition(280, 200);
			text.setString("Game Over");  //Drawing Game Over Text 
			text.setCharacterSize(150);

			Text restartLevelText;
			restartLevelText.setFont(font);
			restartLevelText.setCharacterSize(25);
			string restartTextMaker = "Restarting Game Level " + to_string(*GameLevel);
			restartLevelText.setString(restartTextMaker); //Drawing Restarting Game State
			restartLevelText.setPosition(420, 500);

			window.clear();
			window.draw(restartLevelText);
			window.draw(text);
			window.display();
		}
		changeLevel(&(*GameLevel), window, arr1, &(*coinCount), &(*ObstacleCount), &(*x), &(*y), &(*positionSize)); //Repeating the same Level
	}
}


/**
* Description: LevelEndingPoint() function check if the doodle collect all coins.
* if doodle collect all coins then  appear the level ending button
* @param finishedStatus get number of coins collected by doodle in that level
* @param coinCount get default number of coins according to the level.
*/
void LevelEndingPoint(int* finishedStatus, int* coinCount, Sprite arr1[], RenderWindow& window, int* LevelNo, LevelUpImagePlacer Level1Image[], int* LevelEndBtnPosition) {
	*LevelEndBtnPosition = *LevelNo - 1;
	if (*finishedStatus == (*coinCount) && Level1Image[0].visibleContainer == 0)
	{
		arr1[5].setPosition(Level1Image[0].PlaceX, Level1Image[0].PlaceY); //Draw the LevelUp button.
		window.draw(arr1[5]);
	}
}

/**
* Description: LevelOne() function start the initial Game.
* All other functions are  inside this function.
*/
void LevelOne(double* x, double* y, int* value, bool* jump, double* dy, RenderWindow& window, Sprite arr1[], int* finishedStatus, 
	coinArray CoinArrBuilt[],
	obstaclePositions ObsPos[], LevelUpImagePlacer Imageplacer[], int* levelendBTN, int* GameLevel, int* coinCount, int* ObstacleCount, 
	positions* pos, int* positionSize, int* JumpDownValue) {


	walkingF(&(*value), &(*x)); //walking function 
	jumpF(&(*jump), &(*dy), &(*y));

	window.clear(Color::Blue);
	window.draw(arr1[0]);
	window.draw(arr1[1]);

	FinalScoreDisplay(window);  //final Score display function
	coinMaker(CoinArrBuilt, arr1, window, &(*coinCount));
	MakingObstacles(ObsPos, arr1, window);
	CreateStairs(&(*pos), &(*positionSize), arr1, window);
	stairesSitting(&(*x), &(*y), &(*dy), &(*jump), &(*JumpDownValue), pos, &(*positionSize));
	int ObstacleCollisionReturn = obstacalCollision(&(*x), &(*y), ObsPos, &(*ObstacleCount), window);
	restartCurrentGame(&ObstacleCollisionReturn, window, arr1, &(*x), &(*y), &(*GameLevel), &(*coinCount), &(*ObstacleCount), &(*positionSize));
	coinCollision(&(*x), &(*y), CoinArrBuilt, &(*coinCount), &(*finishedStatus));
	LevelEndingPoint(&(*finishedStatus), &(*coinCount), arr1, window, &(*GameLevel), Imageplacer, &(*levelendBTN));
	checkLevelFinished(&(*x), &(*y), Imageplacer, window, arr1, &(*GameLevel), &(*coinCount), &(*ObstacleCount), &(*finishedStatus), &(*positionSize));
	window.display();
}



int LevelEndBtnPosition = 0;
bool jump = false;
int jump_value = 0;
int JumpDownValue = 0;
int coinCount = 0;
int ObstacleCount = 0;
int positionSize = 0;
int finishedStatus = 0;
double x = 100, y = 500;
double dy = 0;
double dx = 0;
int value = 0;
int deleteVariable = 0;
obstaclePositions* ObsPos;
positions* pos;
coinArray* CoinArrBuilt;
LevelUpImagePlacer* level1Image;



/**
* Description: Levvel1 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level1GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {

	*x = 100;
	*y = 510;
	finishedStatus = 0;
	obstaclePositions* ObsPos2 = new obstaclePositions[2];
	ObsPos2[0].ObsX = 500;
	ObsPos2[0].ObsY = 540;
	ObsPos2[1].ObsX = 570;
	ObsPos2[1].ObsY = 540;

	*ObstacleCount = 2;

	ObsPos = ObsPos2;

	positions* pos2 = new positions[1];
	pos2[0].x = 400;
	pos2[0].y = 450;

	pos = pos2;

	coinArray* CoinArrBuilt2 = new coinArray[1];
	CoinArrBuilt2[0].CoinX = 555;
	CoinArrBuilt2[0].CoinY = 420;
	CoinArrBuilt2[0].objectIdentify = 0;

	*coinCount = 1;

	CoinArrBuilt = CoinArrBuilt2;

	LevelUpImagePlacer* level1Image1 = new LevelUpImagePlacer[1];
	level1Image1[0].PlaceX = 100;
	level1Image1[0].PlaceY = 380;
	level1Image1[0].visibleContainer = 0;

	level1Image = level1Image1;
}



/**
* Description: Level 2 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level4GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {

	finishedStatus = 0;
	*x = 100;   //Default x and Y coordinates
	*y = 510;


	*ObstacleCount = 2;
	obstaclePositions* ObsPos3 = new obstaclePositions[*ObstacleCount];   //obstacle Array
	ObsPos3[0].ObsX = 250;
	ObsPos3[0].ObsY = 540;
	ObsPos3[1].ObsX = 550;
	ObsPos3[1].ObsY = 540;

	ObsPos = ObsPos3;


	*positionSize = 1;
	positions* pos3 = new positions[*positionSize];     //GrassLand Array
	pos3[0].x = 800;
	pos3[0].y = 450;

	pos = pos3;


	*coinCount = 2;
	coinArray* CoinArrBuilt3 = new coinArray[*coinCount];  //Coin Array
	CoinArrBuilt3[0].CoinX = 320;
	CoinArrBuilt3[0].CoinY = 420;
	CoinArrBuilt3[0].objectIdentify = 0;

	CoinArrBuilt3[1].CoinX = 820;
	CoinArrBuilt3[1].CoinY = 400;
	CoinArrBuilt3[1].objectIdentify = 0;

	CoinArrBuilt = CoinArrBuilt3;


	LevelUpImagePlacer* level1Image2 = new LevelUpImagePlacer[1];  //LevelUp Button Array
	level1Image2[0].PlaceX = 100;
	level1Image2[0].PlaceY = 450;
	level1Image2[0].visibleContainer = 0;

	level1Image = level1Image2;
}




/**
* Description: Level3 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level3GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {

	finishedStatus = 0;
	*x = 100;   //Default x and Y coordinates
	*y = 510;


	*ObstacleCount = 2;
	obstaclePositions* ObsPos4 = new obstaclePositions[*ObstacleCount];   //obstacle Array
	ObsPos4[0].ObsX = 400;
	ObsPos4[0].ObsY = 540;
	ObsPos4[1].ObsX = 650;
	ObsPos4[1].ObsY = 540;

	ObsPos = ObsPos4;

	*positionSize = 1;
	positions* pos4 = new positions[*positionSize];   //GrassLand Array
	pos4[0].x = 00;
	pos4[0].y = 490;

	pos = pos4;

	coinArray* CoinArrBuilt4 = new coinArray[2];   //Coin Array
	CoinArrBuilt4[0].CoinX = 555;
	CoinArrBuilt4[0].CoinY = 420;
	CoinArrBuilt4[0].objectIdentify = 0;

	CoinArrBuilt4[1].CoinX = 300;
	CoinArrBuilt4[1].CoinY = 420;
	CoinArrBuilt4[1].objectIdentify = 0;
	*coinCount = 2;

	CoinArrBuilt = CoinArrBuilt4;

	LevelUpImagePlacer* level1Image3 = new LevelUpImagePlacer[1];   //LevelUp Button Array
	level1Image3[0].PlaceX = 100;
	level1Image3[0].PlaceY = 450;
	level1Image3[0].visibleContainer = 0;

	level1Image = level1Image3;
}



/**
* Description: Level4 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level2GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {

	finishedStatus = 0;
	*x = 100;   //Default x and Y coordinates
	*y = 510;


	*ObstacleCount = 1;
	obstaclePositions* ObsPos5 = new obstaclePositions[*ObstacleCount];   //obstacle Array
	ObsPos5[0].ObsX = 250;
	ObsPos5[0].ObsY = 540;

	ObsPos = ObsPos5;

	*positionSize = 1;
	positions* pos5 = new positions[*positionSize];   //GrassLand Array
	pos5[0].x = 720;
	pos5[0].y = 450;

	pos = pos5;


	*coinCount = 2;
	coinArray* CoinArrBuilt5 = new coinArray[*coinCount];   //Coin Array
	CoinArrBuilt5[0].CoinX = 265;
	CoinArrBuilt5[0].CoinY = 420;
	CoinArrBuilt5[0].objectIdentify = 0;

	CoinArrBuilt5[1].CoinX = 680;
	CoinArrBuilt5[1].CoinY = 350;
	CoinArrBuilt5[1].objectIdentify = 0;

	CoinArrBuilt = CoinArrBuilt5;


	LevelUpImagePlacer* level1Image3 = new LevelUpImagePlacer[1];   //LevelUp Button Array
	level1Image3[0].PlaceX = 100;
	level1Image3[0].PlaceY = 450;
	level1Image3[0].visibleContainer = 0;

	level1Image = level1Image3;
}


/**
* Description: Level 2 Game Components
* Obstacles and their positions, coins and coin positions, levelUp button and its position is stated here.
*/
void Level5GameComponents(RenderWindow& window, Sprite arr1[], int* coinCount, int* ObstacleCount, double* x, double* y, int* positionSize) {

	finishedStatus = 0;
	*x = 100;   //Default x and Y coordinates
	*y = 510;


	*ObstacleCount = 3;
	obstaclePositions* ObsPos6 = new obstaclePositions[*ObstacleCount];   //obstacle Array
	ObsPos6[0].ObsX = 400;
	ObsPos6[0].ObsY = 540;
	ObsPos6[1].ObsX = 520;
	ObsPos6[1].ObsY = 540;
	ObsPos6[2].ObsX = 650;
	ObsPos6[2].ObsY = 540;

	ObsPos = ObsPos6;


	*positionSize = 2;
	positions* pos6 = new positions[*positionSize];     //GrassLand Array
	pos6[0].x = 280;
	pos6[0].y = 450;
	pos6[1].x = 580;
	pos6[1].y = 450;

	pos = pos6;


	*coinCount = 2;
	coinArray* CoinArrBuilt6 = new coinArray[*coinCount];  //Coin Array
	CoinArrBuilt6[0].CoinX = 340;
	CoinArrBuilt6[0].CoinY = 350;
	CoinArrBuilt6[0].objectIdentify = 0;

	CoinArrBuilt6[1].CoinX = 500;
	CoinArrBuilt6[1].CoinY = 350;
	CoinArrBuilt6[1].objectIdentify = 0;

	CoinArrBuilt = CoinArrBuilt6;


	LevelUpImagePlacer* level1Image6 = new LevelUpImagePlacer[1];  //LevelUp Button Array
	level1Image6[0].PlaceX = 100;
	level1Image6[0].PlaceY = 450;
	level1Image6[0].visibleContainer = 0;

	level1Image = level1Image6;
}






/**
* Description: UserInputWindow() take players name as an input
*/
void UserInputWindow(RenderWindow& window, Sprite arr1[], Event& ev) {
	window.clear();
	window.draw(arr1[6]);
	fonts.loadFromFile("Poppins.ttf");
	playerText.setFont(fonts);
	playerText.setCharacterSize(35);
	window.setFramerateLimit(11);
	string val = "";

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		NavigationValue = 1010;
		window.setFramerateLimit(60);
	}


	if (ev.type == Event::TextEntered)
	{
		if (isprint(ev.text.unicode))
		{
			playerInput = playerInput + (String)ev.text.unicode;
			val = (String)ev.text.unicode;
		}
		playerText.setString(playerInput);
		cout << val << endl;
		playerText.setPosition(250, 370);

	}

	window.draw(playerText);
	window.display();
}

/**
* Description: InstructionPage() shows the instructions of this Game
*/
void InstructionLoadingPage(RenderWindow& window, Sprite arr1[]) {
	window.setFramerateLimit(11);
	window.clear();
	window.draw(arr1[8]);
	window.display();
	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		NavigationValue = 1020;
		window.setFramerateLimit(60);  //Change Frame Rate
	}
}


/**
* Description: FinalScoreDisplay() function shows the score gaind by the player
*/
void FinalScoreDisplay(RenderWindow& window) {
	Text scoreText;
	Text levelDisplay;
	Font ScoreFont;
	ScoreFont.loadFromFile("Liquidie.ttf");
	scoreText.setFont(ScoreFont);
	levelDisplay.setFont(ScoreFont);
	scoreText.setCharacterSize(35);
	levelDisplay.setCharacterSize(35);
	string printedScore = "Score:  " + to_string(finalScore);
	string printLevelDisplay = "Level: " + to_string(GameLevel);
	scoreText.setString(printedScore);
	levelDisplay.setString(printLevelDisplay);
	scoreText.setPosition(30, 5);
	levelDisplay.setPosition(30, 34);
	window.draw(scoreText);
	window.draw(levelDisplay);
}

/**
* Description: Write Player name and score into a text file
* @param name is the player name
* @param score is the score that player gained
*/

void WriteToFile(string name, int score) {
	//time_t TM = time(0);
	//char* dt = ctime(&TM);
#pragma warning(disable:4996)

// Write to the file

	ifstream myfile;
	myfile.open("results.txt");
	if (myfile) {
		ofstream MyFile("results.txt", ios::app);
		MyFile << "Name : " << name;
		MyFile << "\nScore : " << score;
		//MyFile << "\nDate/time : " << dt;
		MyFile << "\n\n ";
		MyFile.close();
	}
	else {
		ofstream MyFile("results.txt");
		MyFile << "Name : " << name;
		MyFile << "\nScore : " << score;
		//MyFile << "\nDate/time : " << dt;
		MyFile << "\n\n ";
		MyFile.close();

	}
}


/**
* full program runs from here
*/

int main() {
	RenderWindow window(sf::VideoMode(1000, 570), "window");
	Event ev;

	//Textute Array(which contain all images)
	Texture backgrond, boy, jumper, star, obstacle, LevelUp, startWindow, finishGame, InstructionPage;
	Texture arr[9] = { backgrond,boy,jumper ,star,obstacle,LevelUp,startWindow,finishGame,InstructionPage };


	//Sprite Array
	Sprite backgrounds, boys, jumperS, starS, obstacleS, LevelUps, startWindowS, finishGameS, InstructionPageS;
	Sprite arr1[9] = { backgrounds, boys,jumperS,starS, obstacleS,LevelUps,startWindowS,finishGameS,InstructionPageS };
	window.setFramerateLimit(60);



	Level1GameComponents(window, arr1, &coinCount, &ObstacleCount, &x, &y, &positionSize); //load Level1 Components
	LoadingImages(arr, arr1); //loading Images 
	arr1[1].setPosition(x, y);



	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed) {//check if the player close the window
				window.close();
			}
		}
		if (NavigationValue == 100) //Navigating to User Name input 
		{
			UserInputWindow(window, arr1, ev); //user Name input function

		}
		else {
			if (finishingGame)  //finishing the game 
			{
				window.clear();
				window.draw(arr1[7]);
				window.display();
				if (FileWriteCount == 0)
				{
					WriteToFile(playerInput, finalScore);//Writing to the file
					FileWriteCount += 1;
				}

			}
			else if (NavigationValue == 1010)
			{
				InstructionLoadingPage(window, arr1);  //load Instruction Page
			}
			else
			{
				if (ev.type == Event::MouseButtonPressed)
				{
					if (ev.mouseButton.button == Mouse::Left) {//start jumping
						jump = true;
						jump_value = 0;
					}
				}

				arr1[1].setPosition(x, y);
				LevelOne(&x, &y, &value, &jump, &dy, window, arr1, &finishedStatus, CoinArrBuilt, ObsPos, level1Image, &LevelEndBtnPosition, &GameLevel,
					&coinCount, &ObstacleCount, pos, &positionSize, &JumpDownValue);
			}

		}
	}

	return 0;
}



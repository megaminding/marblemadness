#include "StudentWorld.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>

using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath),m_bonusPoints(2000)
{
}



int StudentWorld::init(){
    
    
    //1. Initialize the data structures used to keep track of your game’s world.
    //2. Load the current maze details from a level data file.
    Level lev(assetPath());
    Level::LoadResult result = lev.loadLevel("level00.txt");
    if (result == Level::load_fail_file_not_found){
        cerr << "Could not find level00.txt data file\n";
        return GWSTATUS_NOT_IMPLEMENTED;
    }
    else if (result == Level::load_fail_bad_format){
        cerr << "Your level was improperly formatted\n";
        return GWSTATUS_LEVEL_ERROR;
    }
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level\n";
       
        for (double x = 0; x < VIEW_WIDTH ; x++){
            for (double y = 0; y < VIEW_HEIGHT ; y++){
                Level::MazeEntry ge = lev.getContentsOf(x, y);
                
                switch (ge)
                {
                    case Level::empty:
                        cout << x << "," << y << " is empty\n";
                        
                        break;
                    case Level::exit:
                        cout << x << "," << y << " is where the exit is\n";
                        actors.push_back(new Exits(IID_EXIT, x, y,  -1, 1.0));
                        
                        break;
                    case Level::player:
                        cout << x << "," << y << " is where the player starts\n";
                        player = (new Avatar(IID_PLAYER));
                        break;
                    case Level::horiz_ragebot:
                        cout << x << "," << y << " starts with a horiz. RageBot\n";
                        actors.push_back(new HorizRageBot(IID_RAGEBOT, x, y,  0, 1.0));
                        break;
                    case Level::vert_ragebot:
                        cout << x << "," << y << " starts with a vertical RageBot\n";
                        actors.push_back(new VertRageBot(IID_RAGEBOT, x, y,  0, 1.0));
                        break;
                    case Level::thiefbot_factory:
                        cout << x << "," << y << " holds a ThiefBot factory\n";
                        actors.push_back(new ThiefBotFactory(IID_ROBOT_FACTORY, x, y,  -1, 1.0));
                        break;
                    case Level::mean_thiefbot_factory:
                        cout << x << "," << y << " holds a mean ThiefBot factory\n";
                        actors.push_back(new MeanThiefBotFactory(IID_ROBOT_FACTORY, x, y,  -1, 1.0));
                        break;
                    case Level::wall:
                        cout << "Location " << x << "," << y << " holds a wall\n";
                        actors.push_back(new Walls(IID_WALL, x, y,  -1, 1.0));
                        break;
                    case Level::marble:
                            cout << x << "," << y << " contains a marble\n";
                        actors.push_back(new Marbles(IID_MARBLE, x, y,  -1, 1.0));
                            break;
                        case Level::pit:
                            cout << x << "," << y << " is a pit\n";
                        actors.push_back(new Pits(IID_PIT, x, y,  -1, 1.0));
                            break;
                        case Level::crystal:
                            cout << x << "," << y << " contains a crystal\n";
                        actors.push_back(new Crystals(IID_CRYSTAL, x, y,  -1, 1.0));
                            break;
                        case Level::restore_health:
                            cout << x << "," << y << " contains a health restoration item\n";
                        actors.push_back(new RestoreHealthGoodies(IID_RESTORE_HEALTH, x, y,  0, 1.0));
                            break;
                        case Level::extra_life:
                            cout << x << "," << y << " contains an extra life\n";
                        actors.push_back(new ExtraLifeGoodies(IID_EXTRA_LIFE, x, y,  0, 1.0));
                            break;
                        case Level::ammo:
                            cout << x << "," << y << " contains ammo\n";
                        actors.push_back(new AmmoGoodies(IID_AMMO, x, y,  0, 1.0));
                            break;
                }
                
            }
        }
        cout << "correct WORLD" << this;
        return GWSTATUS_CONTINUE_GAME;
    }
    //3. Allocate and insert a valid Avatar object into the game world.
    //4. Allocate and insert any RageBots objects, wall objects, marble objects, factory
    //objects, crystal objects, goodie objects, or exit objects into the game world, as
    //required by the specification in the current level’s data file.
    
    return GWSTATUS_CONTINUE_GAME;
    
}

string someFunctionToFormatThingsNicely(int score, int level, int lives,
                                 int health, int ammo, int bonus){
    std::string result;

        // Format Score
        result += std::to_string(score);
        
        // Two spaces separator
        result += "  ";

        // Format Level
        result += std::string(2 - std::to_string(level).length(), '0') + std::to_string(level);

        // Two spaces separator
        result += "  ";

        // Format Lives
        result += std::to_string(lives);
        
        // Two spaces separator
        result += "  ";

        // Format Health
        result += std::string(3 - std::to_string(health).length(), ' ') + std::to_string(health) + "%";

        // Two spaces separator
        result += "  ";

        // Format Ammo
        result += std::string(3 - std::to_string(ammo).length(), ' ') + std::to_string(ammo);

        // Two spaces separator
        result += "  ";

        // Format Bonus
        result += std::string(4 - std::to_string(bonus).length(), ' ') + std::to_string(bonus);

        return result;
    
}
void StudentWorld::updateDisplayText()
{

    
    int score = getScore();
     int level = getLevel();
    unsigned int bonus = m_bonusPoints;
    int livesLeft = 3 - getLives();
    int health = player->health();
    int ammo = player->ammo();
//     // Next, create a string from your statistics, of the form:
//     // Score: 0000100 Level: 03 Lives: 3 Health: 70% Ammo: 216 Bonus: 34
     string s = someFunctionToFormatThingsNicely(score, level, livesLeft,
     health, ammo, bonus);
//    // Finally, update the display text at the top of the screen with your
//    // newly created stats
   setGameStatText(s); // calls our provided GameWorld::setGameStatText
}

bool StudentWorld::isValid(int x, int y){
    for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); ++p) {
        Actor* mp = *p;
        
        if (mp->getX() == x &&  mp->getY() == y ){
            if (mp->isObstacle()){
                return false;
            }
        }
    }
    return true;
}

void StudentWorld::test(){
    cout << "HI";
}
void StudentWorld::handlemove(Actor* agentPointer, int ch){
              cout << "ch" << ch;
              // user hit a key this tick!
              switch (ch)
              {
                  case KEY_PRESS_LEFT:
                      cout <<"KEY LEFT";
                      if (isValid(agentPointer->getX()-1, agentPointer->getY())){
                          agentPointer->setDirection(agentPointer->left);
                          agentPointer->moveTo(agentPointer->getX()-1, agentPointer->getY());
                      }
                      
                      break;
                  case KEY_PRESS_RIGHT:
                      cout <<"KEY RIGHT";
                      // ... move avatar to the right ...;
                      if (isValid(agentPointer->getX() + 1, agentPointer->getY())){
                          agentPointer->setDirection(agentPointer->right);
                          agentPointer->moveTo(agentPointer->getX()+1, agentPointer->getY());
                      }
                      
                      break;
                  case KEY_PRESS_UP:
                      cout <<"KEY UP";
                      if (isValid(agentPointer->getX(), agentPointer->getY() + 1)){
                          agentPointer->setDirection(agentPointer->up);
                          agentPointer->moveTo(agentPointer->getX(), agentPointer->getY() +1);
                      }
                      break;
                      
                  case KEY_PRESS_DOWN
                      
                      :
                      cout <<"KEY DOWN";
                      if (isValid(agentPointer->getX(), agentPointer->getY() - 1)){
                          agentPointer->setDirection(agentPointer->down);
                          agentPointer->moveTo(agentPointer->getX(), agentPointer->getY() -1);
                          
                      }
                      break;
                  case KEY_PRESS_SPACE:
                      cout <<"KEY SPACE";
                      //  ... add a pea in the square in front of the avatar...;
                      break;
            //  }
          }
}


int StudentWorld::move()
{
    cout << "MOVE CALLED";
    updateDisplayText();
    cout << m_bonusPoints;
    int ch;
    if (getKey(ch)){
        handlemove(player, ch);

    };
    
    player->doSomething();
    
    for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); ++p) {
        Actor* mp = *p;
        
        if (mp->isVisible()) {
            
            if (!mp->removeOffScreen() ){
                mp->doSomething();
            }
        }
    }

    
   
  
//    If the player steps onto the same square as an exit (after first collecting all
//    of the crystals on the level), completing the current level, then the move()
//    method should immediately:
//    i. Increase the player’s score appropriately (by 2000 points for using
//    the exit, and by the remaining bonus score for the level).
//    ii. Return a value of GWSTATUS_FINISHED_LEVEL.
    
 
    
    
  
//    It must then delete any actors that have died during this tick (e.g., a RageBot that
//    was killed by a pea so both should be removed from the game world, or a goodie
//    that disappeared because the player picked it up).
    for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); ++p) {
            Actor* mp = *p;
        if (mp->removeOffScreen()){
            delete mp;
            list<Actor*>::iterator q = actors.erase(p);
            p = q;
        }
        }
    
    if (player->hasCollectedAllOfTheCrystalsOnTheLevel())
    {
        for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); ++p) {
            Actor* mp = *p;
            if (!mp->isVisible()){
                if (mp->getX() == player->getX() &&  mp->getY() == player->getY() ){
                    mp->makeVisible();
                }
            }
            
        }
    }
      //  exposeTheExitInTheMaze(); // make the exit Active
    
    // This code is here merely to allow the game to build, run, and terminate after you type q
   
    m_bonusPoints = m_bonusPoints - 1;
    
    setGameStatText("Game will end when you type q");
    if (player->health() == 0){
        return GWSTATUS_PLAYER_DIED;
    }
    if (player->checkIfCompletedCurrentLevel())
    {
        increaseScore(2000 + m_bonusPoints);
    return GWSTATUS_FINISHED_LEVEL;
    }
    // the player hasn’t completed the current level and hasn’t died, so
    // continue playing the current level
   
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete player;
    for (list<Actor*>::iterator p = actors.begin(); p != actors.end(); ++p) {
            Actor* mp = *p;
            delete mp;
            list<Actor*>::iterator q = actors.erase(p);
            p = q;
        
        }
    
}

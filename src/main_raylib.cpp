#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "Particle.hpp"
#include "ParticleSet.hpp"
#include "raylib.hpp"

using namespace std;

ParticleSet newSet(int num){
    
    ParticleSet new_set = ParticleSet(num);
    
    for(int i = 0; i < new_set.size(); i++){
        new_set[i].setAcceleration(Vector2D(0.0, 0.0));
    }
    
    return new_set;
}


int main(int argc, char *argv[]){

        int errors = 0;

	if(argc != 3){

	    cerr << "Incorrect number of arguments" << endl;  

	    errors = 1;

	}else{

	    int num = atoi(argv[2]), r = atoi(argv[1]);
	    
	    const int screenWidth = MAX_X;
	    const int screenHeight = MAX_Y;

	    srand(time(0)); //system time as seed for random number generator

	    InitWindow(screenWidth, screenHeight, "Robot Vacuum Cleaner");
	    
	    
	    Particle robot = Particle();
	    
	    robot.setPosition(Vector2D(0.0, 0.0));
	    robot.setAcceleration(Vector2D(0.0, 0.0));
	    robot.setRadius(r);
	    
	    Vector2D initialVelocity = robot.getVelocity();
	    
	    ParticleSet set = newSet(num);
	    
	    bool pause = false;

	    SetTargetFPS(60);
	    
	    while(!WindowShouldClose()){
		
		pause = !(set.size() > 0);
		
		if(IsKeyPressed(KEY_ENTER)){
		    ParticleSet recentSet = newSet(num);
		    set += recentSet;
		}
		
		if(IsKeyPressed(KEY_UP)){
		    if(robot.getVelocity().getY() < 0){
		        robot.setVelocity(Vector2D(robot.getVelocity().getX(), -robot.getVelocity().getY()));
		    }
		}else if(IsKeyPressed(KEY_DOWN)){
		    if(robot.getVelocity().getY() > 0){
		        robot.setVelocity(Vector2D(robot.getVelocity().getX(), -robot.getVelocity().getY()));
		    }
		}else if(IsKeyPressed(KEY_RIGHT)){
		    if(robot.getVelocity().getX() < 0){
		        robot.setVelocity(Vector2D(-robot.getVelocity().getX(), robot.getVelocity().getY()));
		    }
		}else if(IsKeyPressed(KEY_LEFT)){
		    if(robot.getVelocity().getX() > 0){
		        robot.setVelocity(Vector2D(-robot.getVelocity().getX(), robot.getVelocity().getY()));
		    }
		}
		
		
		
		if(!pause){
		    
		    set.handleCollisions();
		    
		    if(robot.getVelocity() == Vector2D(0.0, 0.0)){
		        robot.setVelocity(initialVelocity);
		    }
		    
		    robot.move();
		    robot.bounce();
		    
		    set.move(1);
		    
		    for(int i = 0; i < set.size(); i++){
		        
		        if(robot.collision(set[i])){
		            set -= i;
		        }
		        
		    }
		    
		    
		}else{
		    robot.setVelocity(Vector2D(0.0, 0.0));
		}
		
		BeginDrawing();
		
		    ClearBackground(RAYWHITE);
		    
		    double robotPosX = robot.getPosition().getX();
		    double robotPosY = robot.getPosition().getY();
		    double robotRadio = robot.getRadius();
		    
		    DrawCircle(robotPosX, robotPosY, robotRadio, BLACK);
		    
		    for(int i = 0; i < set.size(); i++){
		        double posX = set[i].getPosition().getX();
		        double posY = set[i].getPosition().getY();
		        double rad = set[i].getRadius();
		        
		        DrawCircle(posX, posY, rad, BLUE);
		        
		    }
		    
		    string particleNumber = "Particles: " + to_string(set.size());
		    
		    DrawText(particleNumber.c_str(), 8, 0, 13, GRAY);
		    
		    DrawText("PRESS ENTER TO ADD PARTICLES", 10, GetScreenHeight() - 25, 20, GRAY);

		    if(pause){
				int fontSize = 40;

				int textWidth = MeasureText("CLEAN ROOM", fontSize);

				int posX = (GetScreenWidth() - textWidth) / 2;

				int posY = (GetScreenHeight() - fontSize) / 2;

		        DrawText("CLEAN ROOM", posX, posY, fontSize, DARKGRAY);
		    }
		    
		EndDrawing();
		
	    }
	    
	    CloseWindow();

	}
    
    return errors;
}

#include <iostream>
using namespace std;
enum Direction { North, South, East, West };
//Mapsite is the common abstract class for all the components of maze
class MapSite
{
	public:
		virtual void Enter() = 0;	
};

class Room : public MapSite {
	public:
		Room(int roomNo){};
		MapSite* GetSide(Direction) const;
		void SetSide(Direction, MapSite*){};
		virtual void Enter(){};

	private:
		MapSite* _sides[4];
		int _roomNumber;
};

class Wall : public MapSite {
	public:
    
		Wall(){};
		virtual void Enter(){};
};

class Door : public MapSite {
	public:
    
		Door(Room* = 0, Room* = 0){};
		Room* OtherSideFrom(Room*);
		virtual void Enter(){};

	private:
		Room* _room1;
		Room* _room2;
		bool _isOpen;	
};


class Maze {
	public:
		Maze(){};
		void AddRoom(Room*){};
		Room* RoomNo(int) const{}
	private:
};

class MazeBuilder {
	public:
		virtual void BuildMaze() { }
		virtual void BuildRoom(int room) { }
		virtual void BuildDoor(int roomFrom, int roomTo) { }
		virtual Maze* GetMaze() { return 0; }
	protected:
		MazeBuilder(){};
};

class MazeGame {
	public:
		MazeGame(){};
		Maze* CreateMaze(MazeBuilder& builder);
};

Maze* MazeGame::CreateMaze(MazeBuilder& builder){
      builder.BuildMaze();
      builder.BuildRoom(1);
      builder.BuildRoom(2);
      builder.BuildRoom(3);
      builder.BuildDoor(1,2);

      return builder.GetMaze();
}

class StandarMazeBuilder : public MazeBuilder{
	public:
		StandarMazeBuilder(){
			_currentMaze = 0;
		}
		virtual void BuildMaze();
		virtual void BuildRoom(int);
		virtual void BuildDoor(int,int);
		virtual Maze* GetMaze();
	private:
		Direction CommonWall(Room*, Room*){};
		Maze* _currentMaze;
};
void StandarMazeBuilder::BuildMaze(){
	_currentMaze = new Maze();
}

Maze* StandarMazeBuilder::GetMaze() {
	return _currentMaze;
}

void StandarMazeBuilder::BuildRoom(int n){
	if (!_currentMaze->RoomNo(n)){
		Room* room = new Room(n);
		_currentMaze->AddRoom(room);

		room->SetSide(North, new Wall);
		room->SetSide(South, new Wall);
		room->SetSide(East, new Wall);
		room->SetSide(West, new Wall);
	}
}
void StandarMazeBuilder::BuildDoor(int n1, int n2){
	Room* r1 = _currentMaze->RoomNo(n1);
	Room* r2 = _currentMaze->RoomNo(n2);
	Door* d = new Door(r1, r2);

	r1->SetSide(CommonWall(r1,r2), d);
	r2->SetSide(CommonWall(r1,r2), d);
}

int main(){
	Maze* maze;
	MazeGame game;
	StandarMazeBuilder builder;
	game.CreateMaze(builder);
	maze = builder.GetMaze();
	return 0;
}











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

class CountingMazeBuilder : public MazeBuilder{
	public:
		CountingMazeBuilder(){
			_rooms = _doors = 0;
		}
		virtual void BuildMaze(){}
		virtual void BuildRoom(int);
		virtual void BuildDoor(int, int);
		virtual void AddWall(int, Direction){}
		void GetCounts(int&, int&) const;
	private:
		int _doors;
		int _rooms;	
};

void CountingMazeBuilder::BuildRoom(int){
	_rooms++;
}
void CountingMazeBuilder::BuildDoor(int, int){
	_doors++;
}
void CountingMazeBuilder::GetCounts(int& rooms, int& doors) const{
	rooms = _rooms;
	cout << _rooms << endl;
	doors = _doors;
}
int main(){
	int rooms, doors;
	MazeGame game;
	CountingMazeBuilder builder;
	game.CreateMaze(builder);
	builder.GetCounts(rooms, doors);

	cout << "The maze has " << rooms << " rooms and " << doors << " doors " << endl;
	return 0;
}











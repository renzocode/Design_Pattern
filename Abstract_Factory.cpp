//side of the room

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
		void SetSide(Direction, MapSite*);
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
		void AddRoom(Room*);
		void AddRoo1(){};
		Room* RoomNo(int) const;
	private:	
};

class MazeFactory : public Maze{
	public:
		MazeFactory(){};
		virtual Maze* MakeMaze() const{
			return new Maze();
		}
		virtual Wall* MakeWall() const{
			return new Wall();
		}
		virtual Room* MakeRoom(int n) const{
			return new Room(n);
		}
		virtual Door* MakeDoor(Room* r1, Room* r2) const{
			return new Door(r1, r1);
		}
};

int main()
{
	MazeFactory* p = new MazeFactory();
	Maze x;
	p->MakeMaze();
	p = (MazeFactory*)p->MakeMaze();
	p->AddRoo1();
	//p = (MazeFactory*)&x;

}






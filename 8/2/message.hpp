

class Message {

public:
	virtual ~Message() {};
};

struct Point3D: public Message {

	Point3D(int _x = 0, int _y = 0, int _z = 0): x(_x), y(_y), z(_z){};
	int x, y, z; 
};

struct Point2D: public Message {

	Point2D(int _x = 0, int _y = 0): x(_x), y(_y){};
	int x, y;
};

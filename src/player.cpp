#include "player.h"

Player::Player() {
	origin = vector3f();
	angles = vector3f();
	
	Init();
}

Player::Player(const vector3f origin) {
	this->origin = origin;
	angles = vector3f();
	
	Init();
}

Player::Player(const vector3f origin, const vector3f angles) {
	this->origin = origin;
	this->angles = angles;
	
	Init();
}

void Player::Init() {
	camera = Camera(origin);
	
	camera.setPitch(angles.x);
	camera.setYaw(angles.y);
	
	camera.setMoveSpeed(SPEED);
	camera.setMouseSpeed(SPEED_MOUSE);
	
	name 	= DEFAULT_NAME;
	health 	= MAX_HEALTH;
	energy 	= DEFAULT_ENERGY;
	
	force = vector3f(0.0f, -0.3f, 0.0f); // gravity too
	direction = vector3f();
	
	onGround = false;
	running = false;
}

void Player::Update(std::vector<Cube>& cubes) {
	if( direction.y >= force.y ) 
		direction += force;
		
	vector3f newPosition = vector3f(camera.getPosition()); 
	newPosition += direction;
		
	vector3f oldPosition = vector3f(newPosition);
		
	for(int i = 0; i < cubes.size(); i++) 
		collision.sphereCube(newPosition, RADIUS, cubes[i]);
		
	if( newPosition.y > oldPosition.y )
		onGround = true;

	UpdatePosition(newPosition);
	
	if( !running && energy < DEFAULT_ENERGY )
		energy += 0.01f;
		
	if( running )
		energy -= 0.05f;
	
	if( energy <= 0.0f )
		setRunning(false);
}

void Player::Draw() {

}

void Player::UpdatePosition(const vector3f vector) {
	origin = vector;
	camera.setPosition(vector);
}

void Player::UpdateAngles() {
	camera.setPitch(angles.x);
	camera.setYaw(angles.y);
}

void Player::setRunning(bool isR) {
	printf("setRunning(%i): energy: %f\n", isR, energy);
	
	if( energy > 3 ) {
		if( isR ) {
			running = true;
			camera.setMoveSpeed(SPEED_RUNNING);
		} else {
			running = isR;
			camera.setMoveSpeed(SPEED);
		}
		
	} else {
		running = false;
		camera.setMoveSpeed(SPEED);
	}
}

void Player::Jump() {
	if( onGround ) {
		onGround = false;
		direction.set(0.0f, JUMP_HEIGHT, 0.0f);
	}
}

// setters & getters
std::string Player::getName() {
	return name;
}

void Player::setName(std::string name) {
	this->name = name;
}
		
vector3f Player::getOrigin() {
	return origin;
}

void Player::setOrigin(vector3f origin) {
	this->origin = origin;
	UpdatePosition(origin);
}
		
vector3f Player::getAngles() {
	return angles;
}

void Player::setAngles(vector3f angles) {
	this->angles = angles;
	UpdateAngles();
}
		
float Player::getHealth() {
	return health;
}

void Player::setHealth(float health) {
	this->health = health;
}

bool Player::isOnGround() {
	return onGround;
}

bool Player::isRunning() {
	return running;
}

Camera* Player::getCamera() {
	return &camera;
}

vector3f Player::findCubeMeshPosition() {
	vector3f sphere = camera.getPosition() + camera.getVector()*30;

	
	float x = sphere.x / Cube::SIZE;
	float y = sphere.y / Cube::SIZE;
	float z = sphere.z / Cube::SIZE;
	
	if( abs(x-floor(x)) >= abs(x-ceil(x)) )
		x = ceil(x);
	else
		x = floor(x);
		
	if( abs(y-floor(y)) >= abs(y-ceil(y)) )
		y = ceil(y);
	else
		y = floor(y);
		
		
	if( abs(z-floor(z)) >= abs(z-ceil(z)) )
		z = ceil(z);
	else
		z = floor(z);
	
	return vector3f(x*Cube::SIZE, y*Cube::SIZE, z*Cube::SIZE);
}
	

void Player::DrawCubeMesh() {
	if( cubeMesh.getID() <= 0 ) {
		cubeMesh = Cube(vector3f(0.0f, 10.0f, 0.0f));
		cubeMesh.setType(GL_LINE_LOOP); // LINE_LOOP STRIP LOOP
		cubeMesh.setColor(vector3f(1.0f, 0.0f, 0.0f));
		cubeMesh.Generate();
		
		printf("Generated: %d!\n", cubeMesh.getID());
	} 

	cubeMesh.Translate(this->findCubeMeshPosition());
	cubeMesh.Draw();
}

void Player::CreateCube(std::vector<Cube>& cubes, unsigned int texture) {
	Cube cube = Cube(this->findCubeMeshPosition()).setTexture(texture);
	cube.setColor(vector3f(0.0f, 0.0f, 0.5f));
	cube.Generate();
	
	cubes.push_back( cube );
}

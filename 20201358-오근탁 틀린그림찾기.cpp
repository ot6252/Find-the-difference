#include <bangtal.h>

using namespace bangtal;


class Rect {
public:
	int centerX, centerY, radius;

	Rect(int cx, int cy, int r) : centerX(cx), centerY(cy), radius(r) {};

	bool checkin(int x, int y) {
		return (x > centerX - radius) && (x < centerX + radius) && (y > centerY - radius) && (y < centerY + radius);
	}
};

int main() 
{

	
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	auto timer = Timer::create(60.f);
	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("Game Over");
		endGame();
		return true;
		});
	

	auto scene0 = Scene::create("시작 화면", "images/여욱.jpg");
	auto scene1 = Scene::create("모나리자", "images/모나리자.png");
	auto scene2 = Scene::create("우유를 따르는 여인", "images/우유를 따르는 여인.png");
	auto scene3 = Scene::create("눈 속의 사냥꾼", "images/눈 속의 사냥꾼.png");

	auto startButton = Object::create("images/start.png", scene0, 1000, 340);
	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		timer->start();
		return true;
	});

	auto endButton = Object::create("images/end.png", scene0, 1000, 280);
	endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
	});

	auto background1 = Object::create("images/모나리자.png", scene1);
	auto background2 = Object::create("images/우유를 따르는 여인.png", scene2);
	auto background3 = Object::create("images/눈 속의 사냥꾼.png", scene3);


	const int num_of_differences1 = 1;
	Rect left_rect1[num_of_differences1] = {
		{295, 555, 30}

	};
	Rect right_rect1[num_of_differences1] = {
		{935, 555, 30},
		
	};



	const int num_of_differences2 = 3;
	Rect left_rect2[num_of_differences2] = {
		{220, 300, 25},
		{45, 610, 25},
		{545, 100, 25}
	};
	Rect right_rect2[num_of_differences2] = {
		{855, 300, 25},
		{685, 610, 25},
		{1185, 100, 25}
	};

	const int num_of_differences3 = 5;
	Rect left_rect3[num_of_differences3] = {
		{385, 90, 20},
		{175, 310, 60},
		{360, 570, 20},
		{540, 60, 25},
		{550, 595, 20}
	};
	Rect right_rect3[num_of_differences3] = {
		{1050, 90, 20},
		{825, 310, 60},
		{1000, 570, 20},
		{1180, 60, 25},
		{1190, 595, 20}
	};





	const int check_size = 25;

	ObjectPtr left_checks1[num_of_differences1];
	ObjectPtr right_checks1[num_of_differences1];

	ObjectPtr left_checks2[num_of_differences2];
	ObjectPtr right_checks2[num_of_differences2];

	ObjectPtr left_checks3[num_of_differences3];
	ObjectPtr right_checks3[num_of_differences3];

	for (int i = 0; i < num_of_differences1; ++i) {
		left_checks1[i] = Object::create("images/check.png", scene1, left_rect1[i].centerX - check_size, left_rect1[i].centerY - check_size, false);
		right_checks1[i] = Object::create("images/check.png", scene1, right_rect1[i].centerX - check_size, right_rect1[i].centerY - check_size, false);
	}

	for (int i = 0; i < num_of_differences2; ++i) {
		left_checks2[i] = Object::create("images/check.png", scene2, left_rect2[i].centerX - check_size, left_rect2[i].centerY - check_size, false);
		right_checks2[i] = Object::create("images/check.png", scene2, right_rect2[i].centerX - check_size, right_rect2[i].centerY - check_size, false);
	}

	for (int i = 0; i < num_of_differences3; ++i) {
		left_checks3[i] = Object::create("images/check.png", scene3, left_rect3[i].centerX - check_size, left_rect3[i].centerY - check_size, false);
		right_checks3[i] = Object::create("images/check.png", scene3, right_rect3[i].centerX - check_size, right_rect3[i].centerY - check_size, false);
	}

	auto count1 = 0;
	auto count2 = 0;
	auto count3 = 0;


	background1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = false;
		for (int i = 0; i < num_of_differences1; ++i) {
			if (left_rect1[i].checkin(x, y) || right_rect1[i].checkin(x, y)) {
				left_checks1[i]->show();
				right_checks1[i]->show();
				checked = true;
				count1++;
			}
		}

		if (checked == false) {
			showMessage("오답입니다");
			scene1->enter();
		}

		if (count1 == num_of_differences1) {
			showMessage("Level 1 Clear");
			scene2->enter();
		}

		return true;
	});

	background2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = false;
		for (int i = 0; i < num_of_differences2; ++i) {
			if (left_rect2[i].checkin(x, y) || right_rect2[i].checkin(x, y)) {
				left_checks2[i]->show();
				right_checks2[i]->show();
				checked = true;
				count2++;
			}
		}

		if (checked == false) {
			showMessage("오답입니다");
			scene2->enter();
			
		}

		if (count2 == num_of_differences2) {
			showMessage("Level 2 Clear");
			scene3->enter();
		}

		return true;
	});

	background3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		bool checked = false;
		for (int i = 0; i < num_of_differences3; ++i) {
			if (left_rect3[i].checkin(x, y) || right_rect3[i].checkin(x, y)) {
				left_checks3[i]->show();
				right_checks3[i]->show();
				checked = true;
				count3++;
			}
		}

		if (checked == false) {
			showMessage("오답입니다");
			scene3->enter();
			
		}

		if (count3 == num_of_differences3) {
			scene0->enter();
			showMessage("Game Clear");
			timer->stop();
			
		}

			return true;
		});


		startGame(scene0);
		
	
		return 0;

	};
#pragma once

enum class ScreenState {

	NONE,
	RUNNING,
	EXIT_APPLICATION,
	CHANGE_NEXT,
	CHANGE_PREVIOS

};

class Game;
class IGameScreen {
protected:
	
	ScreenState _currenState
		= ScreenState::NONE;
	Game* _game = nullptr;
public:
	friend class ScreenList;
	int _screenIndex = 1;
	virtual void checkInput() = 0;
	virtual void initSystem() = 0;
	virtual void build() = 0;
	virtual void destroy() = 0;
	virtual void onExit() = 0;
	virtual void onEntry() = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual int getNextScreen() const = 0;
	virtual int getPreviousScreen() const = 0;
	ScreenState getState() const {
		return _currenState;
	}
	int getIndex() const{
		return _screenIndex;
	}
	void setRunning() {
		_currenState = ScreenState::RUNNING;
	}

	void setParent(Game* game) {
		_game = game;
	}


};

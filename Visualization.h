#ifndef VISUALIZATION_H
#define VISUALIZATION

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Vector>
#include<map>

#include"pathFinding.h"




class Visualization
{
public:
	Visualization();


private:
	//window func
	void windowUpdate();
	void updateWindowDraw();
	void drawGrid();
	void drawText();
	void renderNodes();
	void displayAStarResults();

	//user handeling func
	const bool validateMousePos(const int&, const int&) const;
	void keyDown();
	void keyReleased();
	void mouseButtonDown();
	void mouseButtonReleased();
	void whatIsBeingClicked(const float&, const float&);
	void moveWhereApplicable(const float&, const float&);
	void makeLockedNull();
	void oneTimeLeftClick(const float&, const float&);
	void handleInput();
	void handleEvents();
	
	//interaction func
	void addBarrier(const sf::Vector2f&);
	void manipulatingBarriers(const float&, const float&);
	void removeBarrier();
	bool doesBarrierExist(const sf::Vector2f&);
	bool checkCollide(const sf::Vector2f&);
	void clearAlgorithmVisuals();
	void clearBarricades();

	//backend func
	void startAlgorithm();
	void progressAlgorithm();

	//keys
	bool run_algorithm_key_ = false;
	bool left_click_ = false;
	bool clear_algorithm_visuals_ = false;

	//program states used to ensure the right logical decicions are made at every point while the program is running
	bool locked_on_start_node_ = false;
	bool locked_on_end_node = false;
	bool manip_barriers_ = false;
	bool adding_barriers_ = true;
	bool left_click_toggle_ = false;
	bool clear_barricades_ = false;


	//Window data
	std::unique_ptr<sf::RenderWindow> window_ = nullptr;
	const std::string window_name_ = "A* Algorithm Visualizer";
	sf::VideoMode window_video_mode_;
	const int window_height_ = 960;
	const int window_width_ = 960;
	sf::Event window_event_;

	//Grid variables(need grid class) TEMP
	const float grid_segment_width_ = 20.f;
	const float grid_segment_height_ = 20.f;
	sf::RectangleShape grid_segment_shape_;
	sf::Color grid_segment_fill_color_ = sf::Color::Transparent;
	sf::Color grid_segment_outline_color_ = sf::Color::Black;
	float grid_segment_outline_thickness_ = 1.f;
	const float grid_offset_ = 20.f;
	sf::Vector2f grid_position_container_{0, 0};
	
	//text
	const float text_offset_ = 10.f;//10.f;
	sf::Font font_for_window_text_;
	sf::Text window_text_;
	sf::Vector2f text_position_container_{ 0, 0 };

	//nodeTypes
	float start_node_x_ = 20.f;
	float start_node_y_ = 30.f;

	float end_node_x_ = 920.f;
	float end_node_y_ = 930.f;

	//barricades
	std::vector<sf::Vector2f> list_of_barricades;

	//music
	sf::SoundBuffer bg_music_buffer_;
	sf::Sound bg_music_;

	//pathFinding backend
	pathFinding path_finding_back_end_;
	bool is_path_finding_backend_active_ = false;
	std::vector<std::pair<int, int>> visual_overlay_discovered_nodes_;
	std::vector<std::pair<int, int>> visual_overlay_locked_nodes_;
	std::vector<std::pair<int, int>> visual_overlay_path_;

};

#endif
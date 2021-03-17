#include "Visualization.h"
#include <iostream>

Visualization::Visualization()

{
	//window init stuff
	window_video_mode_.width = window_width_;
	window_video_mode_.height = window_height_;
	window_ = std::make_unique<sf::RenderWindow>(window_video_mode_, window_name_, sf::Style::Close | sf::Style::Titlebar);	
	window_->setFramerateLimit(40);

	//grid init stuff
	grid_segment_shape_.setSize(sf::Vector2f(grid_segment_width_ - 1, grid_segment_height_ - 1));
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);
	grid_segment_shape_.setOutlineColor(grid_segment_outline_color_);
	grid_segment_shape_.setOutlineThickness(grid_segment_outline_thickness_);

	//text init stuff
	font_for_window_text_.loadFromFile("ArialUnicodeMS.ttf");
	window_text_.setFont(font_for_window_text_);
	window_text_.setCharacterSize(15);
	window_text_.setFillColor(sf::Color::Black);


	windowUpdate();
};

void Visualization::drawGrid()
{
	//set grid color
	grid_segment_fill_color_ = sf::Color::Transparent;
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);

	//loop through all possible positions and place a grid segment there
	for (float i = 0 + grid_offset_ + text_offset_; i <  window_height_ - grid_offset_; i+= grid_segment_height_)
	{
		for (float j = 0 + grid_offset_; j < window_width_- grid_offset_; j+= grid_segment_width_)
		{
			grid_position_container_ = { j, i };
			grid_segment_shape_.setPosition(grid_position_container_);
			window_->draw(grid_segment_shape_);
		}
	}
}

void Visualization::drawText()
{
	//responsible for drawing any text to the screen
	text_position_container_ = {10, 3};
	window_text_.setPosition(text_position_container_);
	window_text_.setString("Start: Click & Hold");
	window_->draw(window_text_);

	text_position_container_ = { 145, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  End: Click & Hold");
	window_->draw(window_text_);

	text_position_container_ = { 280, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  Make Barrier: Click");
	window_->draw(window_text_);

	text_position_container_ = { 430, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  Clear Barrier: Click");
	window_->draw(window_text_);
	
	text_position_container_ = { 577, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  Clear* Barriers: V");
	window_->draw(window_text_);

	text_position_container_ = { 715, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  Run A*: R");
	window_->draw(window_text_);

	text_position_container_ = { 800, 3 };
	window_text_.setPosition(text_position_container_);
	window_text_.setString("|  Clear View : C");
	window_->draw(window_text_);

}

void Visualization::renderNodes()
{
	//render the start node
	if (start_node_x_ != -1.f)
	{
		grid_segment_fill_color_ = sf::Color::Green;
		grid_segment_shape_.setFillColor(grid_segment_fill_color_);

		grid_position_container_ = { start_node_x_, start_node_y_ };
		grid_segment_shape_.setPosition(grid_position_container_);
		window_->draw(grid_segment_shape_);
	}

	//render the end node
	if (end_node_x_ != -1.f)
	{
		grid_segment_fill_color_ = sf::Color::Red;
		grid_segment_shape_.setFillColor(grid_segment_fill_color_);

		grid_position_container_ = { end_node_x_, end_node_y_ };
		grid_segment_shape_.setPosition(grid_position_container_);
		window_->draw(grid_segment_shape_);

	}

	//render the barricades
	grid_segment_fill_color_ = sf::Color::Black;
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);

	for (const sf::Vector2f& barricade : list_of_barricades)
	{
		grid_position_container_ = { barricade.x, barricade.y };
		grid_segment_shape_.setPosition(grid_position_container_);
		window_->draw(grid_segment_shape_);
	}
}

const bool Visualization::validateMousePos(const int& x_, const int& y_) const
{
	//if the mouse position is out of visual grid range then mouse position is invalid
	if (x_ < grid_offset_ || x_ > window_width_ - grid_offset_-1)
		return false;

	if (y_ < grid_offset_ + text_offset_ || y_ > window_width_ - text_offset_-1)
		return false;
	
	return true;
}

bool Visualization::checkCollide(const sf::Vector2f& new_pos_)
{
	//if new pos is colliding with start, end or any barricade nodes then collision is detected
	if (new_pos_ == sf::Vector2f{ start_node_x_, start_node_y_ })
		return true;

	if (new_pos_ == sf::Vector2f{ end_node_x_, end_node_y_ })
		return true;

	for (const sf::Vector2f& pos_ : list_of_barricades)
	{
		if (pos_ == new_pos_)
			return true;
	}

	return false;

}

void Visualization::addBarrier(const sf::Vector2f& barrier)
{
	//loop through all barriers, if barrier exists then dont add it. If it does not exist then add it
	for (const sf::Vector2f& barricade : list_of_barricades)
	{
		if(checkCollide(barrier))
			return;
	}
	list_of_barricades.emplace_back(barrier);

}

void Visualization::displayAStarResults()
{
	//loop through all the discovered nodes and pass data in rectange shape and render to screen
	grid_segment_fill_color_ = sf::Color::Color(0, 255, 0, 80);
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);
	for (const std::pair<int, int>& pos_ : visual_overlay_discovered_nodes_)
	{
		grid_segment_shape_.setPosition(sf::Vector2f(pos_.second*grid_segment_width_ + grid_offset_, pos_.first*grid_segment_height_ + grid_offset_+text_offset_));
		window_->draw(grid_segment_shape_);
	}


	//loop through all the locked nodes and pass data in rectange shape and render to scree
	grid_segment_fill_color_ = sf::Color::Color(0, 0, 255, 80);
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);
	for (const std::pair<int, int>& pos_ : visual_overlay_locked_nodes_)
	{
		grid_segment_shape_.setPosition(sf::Vector2f(pos_.second * grid_segment_width_ + grid_offset_, pos_.first * grid_segment_height_ + grid_offset_ + text_offset_));
		window_->draw(grid_segment_shape_);
	}

	//fill in the path from start to end if no path exists
	if (visual_overlay_path_.empty())
	{
		std::pair<int, int> prev_ = path_finding_back_end_.graph[path_finding_back_end_.endNodePosY][path_finding_back_end_.endNodePosX].parentPos;

		while (prev_.first != 999)
		{
			visual_overlay_path_.emplace_back(prev_);
			prev_ = path_finding_back_end_.graph[prev_.first][prev_.second].parentPos;
		}
	}

	//render the path from start to end nodes
	grid_segment_fill_color_ = sf::Color::Color(255, 255, 0, 200);
	grid_segment_shape_.setFillColor(grid_segment_fill_color_);
	for (const std::pair<int, int>& position_ : visual_overlay_path_)
	{
		grid_segment_shape_.setPosition(sf::Vector2f(position_.second * grid_segment_width_ + grid_offset_, position_.first * grid_segment_height_ + grid_offset_ + text_offset_));
		window_->draw(grid_segment_shape_);
	}
}

void Visualization::keyDown()
{
	//R is the key to run the algorithm
	if (window_event_.key.code == sf::Keyboard::R)
		run_algorithm_key_ = true;
	if (window_event_.key.code == sf::Keyboard::C)
		clear_algorithm_visuals_ = true;
	if (window_event_.key.code == sf::Keyboard::V)
		clear_barricades_ = true;
}

void Visualization::keyReleased()
{
	if (window_event_.key.code == sf::Keyboard::R)
		run_algorithm_key_ = false;
	if (window_event_.key.code == sf::Keyboard::C)
		clear_algorithm_visuals_ = false;
	if (window_event_.key.code == sf::Keyboard::V)
		clear_barricades_ = false;
}

void Visualization::mouseButtonDown()
{
	if (window_event_.mouseButton.button == sf::Mouse::Left)
		left_click_ = true;
}

void Visualization::mouseButtonReleased()
{
	if (window_event_.mouseButton.button == sf::Mouse::Left)
	{
		//reset program state
		left_click_ = false;
		path_finding_back_end_.clearClickedStatus();
		manip_barriers_ = false;
		left_click_toggle_ = false;
	}

}

void Visualization::removeBarrier() 
{
	//get position of barrier 
	float barricade_x = std::floor(sf::Mouse::getPosition(*window_).x / grid_segment_width_) * grid_segment_width_;
	float barricade_y = std::floor((sf::Mouse::getPosition(*window_).y - text_offset_) / grid_segment_height_) * grid_segment_height_ + text_offset_;
	
	//see if barricade exists
	for (unsigned int i = 0; i < list_of_barricades.size(); i++)
	{
		if (list_of_barricades[i].x == barricade_x && list_of_barricades[i].y == barricade_y)
			list_of_barricades.erase(list_of_barricades.begin() + i);
	}
}

void Visualization::startAlgorithm()
{
	//reset alg data for re-run
		clearAlgorithmVisuals();

		//set start and end nodes
		path_finding_back_end_.startNodePosX = int(start_node_x_ / grid_segment_width_) - 1;
		path_finding_back_end_.startNodePosY = int((start_node_y_ - text_offset_) / grid_segment_height_) - 1;

		path_finding_back_end_.endNodePosX = int(end_node_x_ / grid_segment_width_) - 1;
		path_finding_back_end_.endNodePosY = int((end_node_y_ - text_offset_) / grid_segment_height_ )- 1;

		//init the algorithm data
		path_finding_back_end_.addToHeap({ path_finding_back_end_.startNodePosY ,path_finding_back_end_.startNodePosX });

		path_finding_back_end_.graph[path_finding_back_end_.startNodePosY][path_finding_back_end_.startNodePosX].gCost = 0;

		//convert all barricades into positions relative to graph then add them to the graph
		for (unsigned int i = 0; i < list_of_barricades.size(); i++)
		{
			int barricade_y_ = int((list_of_barricades[i].y - text_offset_) / grid_segment_height_) - 1;
			int barricade_x_ = int(list_of_barricades[i].x / grid_segment_width_ - 1);
			path_finding_back_end_.graph[barricade_y_][barricade_x_].isNodeWall = true;
		}

		//set the anim state to active
		is_path_finding_backend_active_ = true;
	

	if (path_finding_back_end_.isDone)//if user tries to run again and alg anim is done then reset anim states
	{
		is_path_finding_backend_active_ = false;
		path_finding_back_end_.isDone = false;
	}
}

void Visualization::progressAlgorithm()
{
	//make a single cycle through A* alg
	if (is_path_finding_backend_active_)
	{
		if (!path_finding_back_end_.isDone)
			path_finding_back_end_.AstartAlg(visual_overlay_discovered_nodes_, visual_overlay_locked_nodes_);
		else
			is_path_finding_backend_active_ = false;
	}
}

void Visualization::updateWindowDraw()
{
	//draw all window modules

	drawGrid();//draw window grid
	drawText();//draw window text
	progressAlgorithm();//make a move on algorithm
	displayAStarResults();//display results
	renderNodes();//render nodes
}

bool Visualization::doesBarrierExist(const sf::Vector2f& given_pos_)
{
	//look through all barriers to see if barrier passed exists
	for (const sf::Vector2f& barrier : list_of_barricades)
	{
		if (barrier == given_pos_)
			return true;
	}
	return false;
}

void Visualization::oneTimeLeftClick(const float& new_start_node_x_, const float& new_start_node_y_)
{
	if (!left_click_toggle_)//1 time click toggle check for first left click of all left clicks in left click generation
	{
		left_click_toggle_ = true;//activate toggle so cant find node type again until click release and click press
		if (doesBarrierExist({ new_start_node_x_, new_start_node_y_ }))//if a barrier is under mouse then set state to remove barriers
			adding_barriers_ = false;
		else//if barrier does not exist under mouse then set state to adding barriers
			adding_barriers_ = true;
	}
}

void Visualization::manipulatingBarriers(const float& new_start_node_x_, const float& new_start_node_y_)
{
	int y_ = int((new_start_node_y_ - text_offset_) / grid_segment_height_) - 1;//use thease positions to set node clicked on states in the graph
	int x_ = int(new_start_node_x_ / grid_segment_width_) - 1;

	manip_barriers_ = true;

	if (!(path_finding_back_end_.graph[y_][x_].has_been_clicked_on_))//if node hasnt been toggled
	{
		path_finding_back_end_.graph[y_][x_].has_been_clicked_on_ = true;//make toggled

		if (adding_barriers_)//if adding state then add else remove
			addBarrier(sf::Vector2f(new_start_node_x_, new_start_node_y_));
		else
			removeBarrier();

	}
}

void Visualization::whatIsBeingClicked(const float& new_start_node_x_ , const float& new_start_node_y_)
{
		//if hold on start and not currently manipulating any other area then lock start to mouse while hold click
		if (start_node_x_ == new_start_node_x_ && start_node_y_ == new_start_node_y_ && !locked_on_end_node && !manip_barriers_)
			locked_on_start_node_ = true;
		
		//if hold on end and not currently manipulating any other area then lock start to mouse while hold click
		else if (end_node_x_ == new_start_node_x_ && end_node_y_ == new_start_node_y_ && !locked_on_start_node_ && !manip_barriers_)
			locked_on_end_node = true;

		//if not manip start or end node and clicked then must be manip barricades
		else if (!locked_on_end_node && !locked_on_start_node_)
		{
			oneTimeLeftClick(new_start_node_x_, new_start_node_y_);
			manipulatingBarriers(new_start_node_x_, new_start_node_y_);
		}
		
}

void Visualization::moveWhereApplicable(const float& new_pos_x_, const float& new_pos_y_)
{
	//used to move start and end nodes as long as current mouse position is not a position of conflict
	if (locked_on_start_node_)
	{
		if (!checkCollide(sf::Vector2f(new_pos_x_, new_pos_y_)))
		{
			start_node_x_ = new_pos_x_;
			start_node_y_ = new_pos_y_;
		}
	}

	if (locked_on_end_node)
	{
		if (!checkCollide(sf::Vector2f(new_pos_x_, new_pos_y_)))
		{
			end_node_x_ = new_pos_x_;
			end_node_y_ = new_pos_y_;
		}
	}
}

void Visualization::clearAlgorithmVisuals()
{
	//disable further iterations of algorithm
	is_path_finding_backend_active_ = false;

	//clear the visuals
	visual_overlay_discovered_nodes_.clear();
	visual_overlay_locked_nodes_.clear();
	visual_overlay_path_.clear();

	//reset the backend of the algorithm
	path_finding_back_end_.clearHeap();
	path_finding_back_end_.resetGraph();

}

void Visualization::makeLockedNull()
{
	//reset all states on program
	locked_on_start_node_ = false;
	locked_on_end_node = false;
	manip_barriers_ = false;
}

void Visualization::clearBarricades()
{
	list_of_barricades.clear();
}

void Visualization::handleInput()
{
	//get new position relative to grid positions
	float new_start_node_x_ = std::floor(sf::Mouse::getPosition(*window_).x / grid_segment_width_) * grid_segment_width_;
	float new_start_node_y_ = std::floor((sf::Mouse::getPosition(*window_).y - text_offset_) / grid_segment_height_) * grid_segment_height_ + text_offset_;

	if (left_click_)//if selecting node get what is being selected
		whatIsBeingClicked(new_start_node_x_, new_start_node_y_);

	else
		makeLockedNull();//if nothing is being selected then make all selected false

	if (clear_barricades_)
		clearBarricades();

	moveWhereApplicable(new_start_node_x_, new_start_node_y_);//update what needs to be updated
}

void Visualization::handleEvents()
{
	switch (window_event_.type)
	{
	case sf::Event::Closed:
		window_->close();
		break;

	case sf::Event::KeyPressed:
		keyDown();
		break;

	case sf::Event::KeyReleased:
		keyReleased();
		break;

	case sf::Event::MouseButtonPressed:
		mouseButtonDown();
		break;

	case sf::Event::MouseButtonReleased:
		mouseButtonReleased();
		break;

	}
}

void Visualization::windowUpdate()
{
	while (window_->isOpen())
	{
			//input state
		while (window_->pollEvent(window_event_))
			handleEvents();
			
		if (!is_path_finding_backend_active_)//if can do input
		{//check if in state to give input
			if (validateMousePos(sf::Mouse::getPosition(*window_).x, sf::Mouse::getPosition(*window_).y))
				handleInput();//then check for input type
		}

		//run the algorithm
		if (run_algorithm_key_)
			startAlgorithm();

		//if reset visuals
		if (clear_algorithm_visuals_)
			clearAlgorithmVisuals();

		window_->clear(sf::Color::Color(211, 211, 211, 80));
		updateWindowDraw();
		window_->display();

	}
}
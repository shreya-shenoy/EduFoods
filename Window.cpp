#include <SFML/Graphics.hpp>
#include "Window.h"
#include "DataExtract.h"
#include "Tree.h"
#include "HashTable.h"
#include <set>

int main() {
    string filename = "FoodProducts2.csv";
    DataExtract sheet;
    vector<vector<string>> data = sheet.extractData(filename);

    std::ifstream file(filename);

    Tree tree;
    HashTable table;
    set<string> s;
    // CREATING AND INITIALIZING 20-ARY TREE AND HASH TABLE
    for(int i = 1; i < 20000; i++) // upper bound set to 15 (instead of data.size()) for debugging
    {
        if(data.at(i).size() >= 12) // make sure the row size is at least 12, gets rid of data points w/ missing entries
        {
            string date = data.at(i).at(0);
            string product  = "";
            int index = 4;
            // add product entry without commas
            for(int j = 4; j < data.at(i).size(); j++){
                if(j == 4 && data.at(i).at(j).front() != '"'){
                    product =  data.at(i).at(j);
                    break;
                }

                if (j != 4 && !data.at(i).at(j).empty() &&
                    data.at(i).at(j).back() == '"') {
                    product += data.at(i).at(j) + " ";
                    index = j;
                    break;
                }
                product += data.at(i).at(j) + " ";
            }
            index+=2;
            string category = "";
            // add category entry without commas
            for(int j = index; j < data.at(i).size(); j++){
                if(j == index && data.at(i).at(j).front() != '"'){
                    category =  data.at(i).at(j);
                    break;
                }

                if (j != index && !data.at(i).at(j).empty() &&
                    data.at(i).at(j).back() == '"') {
                    category += data.at(i).at(j) + " ";
                    index = j;
                    break;
                }
                category += data.at(i).at(j) + " ";
            }

            string symptoms = "";
            index += 4;
            // add symptoms entry without commas
            for(int j = index; j < data.at(i).size(); j++){
                if(j == index && data.at(i).at(j).front() != '"'){
                    symptoms =  data.at(i).at(j);
                    break;
                }

                if (j != index && !data.at(i).at(j).empty() &&
                    data.at(i).at(j).back() == '"') {
                    symptoms += data.at(i).at(j) + " ";
                    index = j;
                    break;
                }
                symptoms += data.at(i).at(j) + " ";
            }
            s.insert(category);

            tree.insert(date, product, category, symptoms); // insert into tree
            table.insert(date, product, category, symptoms); // insert into hash table
        }

    }






///////////////////////////////////////////
//////////////////////////////////////////


// SFML WINDOW SETUP

    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "EduFoods");

    sf::Font font;
    sf::Text welcomeText, intro, time_text;

    sf::RectangleShape scrollBar(sf::Vector2f(20, 600));
    scrollBar.setFillColor(sf::Color::Black);
    float scrollPosition = 0.0f;

    sf::RectangleShape content(sf::Vector2f(200, 200));
    content.setFillColor(sf::Color(116, 193, 232, 255));
    content.setPosition(100, 275);

    if(!font.loadFromFile("font.ttf"))
        cout << "error" << endl;
    welcomeText.setFont(font);
    welcomeText.setCharacterSize(35);
    welcomeText.setFillColor(sf::Color(91, 101, 166, 255));
    welcomeText.setStyle(sf::Text::Bold);

    welcomeText.setString("EduFoods: Informing Adverse Reactions");
    sf::FloatRect textRect = welcomeText.getLocalBounds();
    welcomeText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    welcomeText.setPosition(sf::Vector2f(800/2.0f, 400/2.0f -150));

    sf::Text outputText;


    outputText.setFont(font);
    outputText.setCharacterSize(14);
    outputText.setFillColor(sf::Color(55, 69, 164, 255));
    outputText.setStyle(sf::Text::Bold);
    outputText.setString("");
    string output = "";

    sf::Text selectedYear;


    selectedYear.setFont(font);
    selectedYear.setCharacterSize(13);
    selectedYear.setFillColor(sf::Color::Blue);
    selectedYear.setStyle(sf::Text::Bold);
    selectedYear.setString("");
    string chosenYear = "";


    sf::Text selectedCat;


    selectedCat.setFont(font);
    selectedCat.setCharacterSize(13);
    selectedCat.setFillColor(sf::Color::Blue);
    selectedCat.setStyle(sf::Text::Bold);
    selectedCat.setString("");
    string chosenCat = "";

    sf::Text selectedType;


    selectedType.setFont(font);
    selectedType.setCharacterSize(13);
    selectedType.setFillColor(sf::Color::Blue);
    selectedType.setStyle(sf::Text::Bold);
    selectedType.setString("");
    string chosenType = "";

    sf::Text selectedStructure;


    selectedStructure.setFont(font);
    selectedStructure.setCharacterSize(13);
    selectedStructure.setFillColor(sf::Color::Blue);
    selectedStructure.setStyle(sf::Text::Bold);
    selectedStructure.setString("");
    string chosenStructure = "";


    intro.setFont(font);
    intro.setCharacterSize(23);
    intro.setFillColor(sf::Color(91, 101, 166, 255));
    intro.setStyle(sf::Text::Bold);
    //welcomeText.setPosition(800/2.0f - 800/4.0f, 600/2.0f -150);

    intro.setString("To learn more about adverse consumer events, \n\n please select the filters below.");
    sf::FloatRect textRect2 = welcomeText.getLocalBounds();
    intro.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
    intro.setPosition(sf::Vector2f(800/2.0f, 500/2.0f -150));


    //ELAPSED TIME
    time_text.setFont(font);
    time_text.setCharacterSize(17);
    time_text.setFillColor(sf::Color(72, 73, 64, 255));
    time_text.setStyle(sf::Text::Bold);
    time_text.setPosition(800/2.0f - 800/4.0f, 600/2.0f -150);



    // DROP DOWN MENU 1: PRODUCT CATEGORIES
    sf::RectangleShape dropdownButton(sf::Vector2f(150, 25));
    dropdownButton.setFillColor(sf::Color(38, 129, 175, 255));
    dropdownButton.setPosition(400, 200);

    // Dropdown menu options
    sf::RectangleShape option1(sf::Vector2f(150, 25));
    option1.setFillColor(sf::Color(116, 193, 232, 255));
    option1.setPosition(400, 225);

    sf::RectangleShape option2(sf::Vector2f(150, 25));
    option2.setFillColor(sf::Color(116, 193, 232, 255));
    option2.setPosition(400, 250);

    sf::RectangleShape option3(sf::Vector2f(150, 25));
    option3.setFillColor(sf::Color(116, 193, 232, 255));
    option3.setPosition(400, 275);

    sf::RectangleShape option4(sf::Vector2f(150, 25));
    option4.setFillColor(sf::Color(116, 193, 232, 255));
    option4.setPosition(400, 300);

    sf::RectangleShape option5(sf::Vector2f(150, 25));
    option5.setFillColor(sf::Color(116, 193, 232, 255));
    option5.setPosition(400, 325);

    sf::RectangleShape option6(sf::Vector2f(150, 25));
    option6.setFillColor(sf::Color(116, 193, 232, 255));
    option6.setPosition(400, 350);

    sf::RectangleShape option7(sf::Vector2f(150, 25));
    option7.setFillColor(sf::Color(116, 193, 232, 255));
    option7.setPosition(400, 375);

    sf::RectangleShape option8(sf::Vector2f(150, 25));
    option8.setFillColor(sf::Color(116, 193, 232, 255));
    option8.setPosition(400, 400);

    sf::RectangleShape option9(sf::Vector2f(150, 25));
    option9.setFillColor(sf::Color(116, 193, 232, 255));
    option9.setPosition(400, 425);

    sf::RectangleShape option10(sf::Vector2f(150, 25));
    option10.setFillColor(sf::Color(116, 193, 232, 255));
    option10.setPosition(400, 450);

    // Text for options

    font.loadFromFile("font.ttf"); // Replace with the path to your font file

    sf::Text dropDown1("Product Category", font, 15);
    dropDown1.setPosition(410, 205);

    sf::Text textOption1("Meat Products", font, 15);
    textOption1.setPosition(410, 230);

    sf::Text textOption2("Cereal Prep/Breakfast Foods", font, 15);
    textOption2.setPosition(410, 255);

    sf::Text textOption3("Cheese Products", font, 15);
    textOption3.setPosition(410, 280);

    sf::Text textOption4("Cosmetics", font, 15);
    textOption4.setPosition(410, 305);

    sf::Text textOption5("Fishery/Seafood Products", font, 15);
    textOption5.setPosition(410, 330);

    sf::Text textOption6("Snack Foods", font, 15);
    textOption6.setPosition(410, 355);

    sf::Text textOption7("Soft Drink/Water", font, 15);
    textOption7.setPosition(410, 380);

    sf::Text textOption8("Vegetables", font, 15);
    textOption8.setPosition(410, 405);

    sf::Text textOption9("Vitamins/Minerals", font, 15);
    textOption9.setPosition(410, 430);

    sf::Text textOption10("Whole Grain/Milled Grain", font, 15);
    textOption10.setPosition(410, 455);



    bool isDropdown_catOpen = false;





    // DROP DOWN MENU 2: DATE CATEGORIES //////////////////////////////////////
    sf::RectangleShape dropdownButton_dates(sf::Vector2f(150, 25));
    dropdownButton_dates.setFillColor(sf::Color(38, 129, 175, 255));
    dropdownButton_dates.setPosition(200, 200);

    // Dropdown menu options
    sf::RectangleShape option1_dates(sf::Vector2f(150, 25));
    option1_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option1_dates.setPosition(200, 225);

    sf::RectangleShape option2_dates(sf::Vector2f(150, 25));
    option2_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option2_dates.setPosition(200, 250);

    sf::RectangleShape option3_dates(sf::Vector2f(150, 25));
    option3_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option3_dates.setPosition(200, 275);

    sf::RectangleShape option4_dates(sf::Vector2f(150, 25));
    option4_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option4_dates.setPosition(200, 300);

    sf::RectangleShape option5_dates(sf::Vector2f(150, 25));
    option5_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option5_dates.setPosition(200, 325);

    sf::RectangleShape option6_dates(sf::Vector2f(150, 25));
    option6_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option6_dates.setPosition(200, 350);

    sf::RectangleShape option7_dates(sf::Vector2f(150, 25));
    option7_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option7_dates.setPosition(200, 375);

    sf::RectangleShape option8_dates(sf::Vector2f(150, 25));
    option8_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option8_dates.setPosition(200, 400);

    sf::RectangleShape option9_dates(sf::Vector2f(150, 25));
    option9_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option9_dates.setPosition(200, 425);

    sf::RectangleShape option10_dates(sf::Vector2f(150, 25));
    option10_dates.setFillColor(sf::Color(116, 193, 232, 255));
    option10_dates.setPosition(200, 450);

    // Text for options

    font.loadFromFile("font.ttf"); // Replace with the path to your font file

    sf::Text dropDown1_dates("Dates", font, 15);
    dropDown1_dates.setPosition(250, 205);

    sf::Text textOption1_dates("2023", font, 15);
    textOption1_dates.setPosition(210, 230);

    sf::Text textOption2_dates("2022", font, 15);
    textOption2_dates.setPosition(210, 255);

    sf::Text textOption3_dates("2021", font, 15);
    textOption3_dates.setPosition(210, 280);

    sf::Text textOption4_dates("2020", font, 15);
    textOption4_dates.setPosition(210, 305);

    sf::Text textOption5_dates("2019", font, 15);
    textOption5_dates.setPosition(210, 330);

    sf::Text textOption6_dates("2018", font, 15);
    textOption6_dates.setPosition(210, 355);

    sf::Text textOption7_dates("2017", font, 15);
    textOption7_dates.setPosition(210, 380);

    sf::Text textOption8_dates("2016", font, 15);
    textOption8_dates.setPosition(210, 405);

    sf::Text textOption9_dates("2015", font, 15);
    textOption9_dates.setPosition(210, 430);

    sf::Text textOption10_dates("2014", font, 15);
    textOption10_dates.setPosition(210, 455);


    // DROP DOWN 3: OUTPUT TYPES //////////////////////////////

    bool isDropdown_OutputOpen = false;
    sf::RectangleShape dropdownButton_output(sf::Vector2f(150, 25));
    dropdownButton_output.setFillColor(sf::Color(38, 129, 175, 255));
    dropdownButton_output.setPosition(600, 200);

    // Dropdown menu options
    sf::RectangleShape option1_output(sf::Vector2f(150, 25));
    option1_output.setFillColor(sf::Color(116, 193, 232, 255));
    option1_output.setPosition(600, 225);

    sf::RectangleShape option2_output(sf::Vector2f(150, 25));
    option2_output.setFillColor(sf::Color(116, 193, 232, 255));
    option2_output.setPosition(600, 250);

    sf::RectangleShape option3_output(sf::Vector2f(150, 25));
    option3_output.setFillColor(sf::Color(116, 193, 232, 255));
    option3_output.setPosition(600, 275);

    sf::RectangleShape option4_output(sf::Vector2f(150, 25));
    option4_output.setFillColor(sf::Color(116, 193, 232, 255));
    option4_output.setPosition(600, 300);

    sf::RectangleShape option5_output(sf::Vector2f(150, 25));
    option5_output.setFillColor(sf::Color(116, 193, 232, 255));
    option5_output.setPosition(600, 325);

    // Text for options

    font.loadFromFile("font.ttf"); // Replace with the path to your font file

    sf::Text dropDown1_output("Output Types", font, 15);
    dropDown1_output.setPosition(620, 205);

    sf::Text textOption1_output("All info", font, 15);
    textOption1_output.setPosition(610, 230);

    sf::Text textOption2_output("Dates", font, 15);
    textOption2_output.setPosition(610, 255);

    sf::Text textOption3_output("Product Names", font, 15);
    textOption3_output.setPosition(610, 280);

    sf::Text textOption4_output("Symptoms", font, 15);
    textOption4_output.setPosition(610, 305);

    sf::Text textOption5_output("Number of Cases", font, 15);
    textOption5_output.setPosition(610, 330);

    // DROP DOWN 4: DATA STRUCTURES //////////////////////////////

    bool isDropdown_StructureOpen = false;
    sf::RectangleShape dropdownButton_structure(sf::Vector2f(150, 25));
    dropdownButton_structure.setFillColor(sf::Color(38, 129, 175, 255));
    dropdownButton_structure.setPosition(30, 200);

    // Dropdown menu options
    sf::RectangleShape option1_structure(sf::Vector2f(150, 25));
    option1_structure.setFillColor(sf::Color(116, 193, 232, 255));
    option1_structure.setPosition(30, 225);

    sf::RectangleShape option2_structure(sf::Vector2f(150, 25));
    option2_structure.setFillColor(sf::Color(116, 193, 232, 255));
    option2_structure.setPosition(30, 250);

    sf::RectangleShape option3_structure(sf::Vector2f(150, 25));
    option3_structure.setFillColor(sf::Color(116, 193, 232, 255));
    option3_structure.setPosition(30, 275);


    // Text for options

    font.loadFromFile("font.ttf"); // Replace with the path to your font file

    sf::Text dropDown1_structure("Data Structure", font, 15);
    dropDown1_structure.setPosition(40, 205);

    sf::Text textOption1_structure("20-ary Tree", font, 15);
    textOption1_structure.setPosition(40, 230);

    sf::Text textOption2_structure("Hash Table", font, 15);
    textOption2_structure.setPosition(40, 255);

    /*sf::Text textOption3_structure("Both Structures", font, 15);
    textOption3_structure.setPosition(40, 280);
*/

//////////////////////////////////////



    bool isDropdown_datesOpen = false;
    bool usingTree = false;
    bool usingTable = false;
    bool usingBoth = false;
    bool isOutput_select=false; // seeing if specific output selected
    float totalTime=0; //for total clock time to perform operation

    string category = "";
    string year = "";
    vector<Node> treeNodes;
    vector<Node> tableNodes;
    int outputOption = 0;
    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    scrollPosition -= event.mouseWheelScroll.delta * 10.0f;
                    // Ensure scroll position stays within bounds
                    scrollPosition = std::max(0.0f, std::min(scrollPosition, content.getSize().y - window.getSize().y));
                }
            }

            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Mouse mouse;
                auto coordinate = mouse.getPosition(window);
                // CHECK IF DROPDOWN 1 CLICKED
                if (dropdownButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                    cout << "CLICKED" << endl;
                    isDropdown_catOpen = true;
                }
                else if (dropdownButton_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                    cout << "CLICKED" << endl;
                    isDropdown_datesOpen = true;
                }
                else if (dropdownButton_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                    cout << "CLICKED" << endl;
                    isDropdown_OutputOpen = true;
                }
                else if (dropdownButton_structure.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                    cout << "CLICKED" << endl;
                    isDropdown_StructureOpen = true;
                }

                if (isDropdown_catOpen) { ////////////// CATEGORY DROPDOWN
                    if (option1.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "\"Meat Meat Products and Poultry\" ";

                        tree.setCategory(category);
                        table.setCategory(category);
                        chosenCat = "You've selected: \n\n" + category;
                        cout << "MEAT" << tree.getCategory() << endl;
                        isDropdown_catOpen = false;
                    } else if (option2.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Cereal Prep/Breakfast Food";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option3.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Cheese/Cheese Prod";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option4.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Cosmetics";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option5.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Fishery/Seafood Prod";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option6.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Snack Food Item";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option7.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Soft Drink/Water";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option8.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Vegetables/Vegetable Products";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option9.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Vit/Min/Prot/Unconv Diet(Human/Animal)";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                    else if (option10.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        category = "Whole Grain/Milled Grain Prod/Starch";
                        chosenCat = "You've selected: \n\n" + category;
                        tree.setCategory(category);
                        table.setCategory(category);
                        isDropdown_catOpen = false;
                    }
                }
                else  if (isDropdown_datesOpen) { //////////////
                    if (option1_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        cout << "2023" << endl;
                        year = "2023";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    } else if (option2_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2022";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option3_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2021";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option4_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2020";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option5_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2019";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option6_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2018";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option7_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2017";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option8_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2016";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option9_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2015";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }
                    else if (option10_dates.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        year = "2014";
                        tree.setYear(year);
                        table.setYear(year);
                        chosenYear = "You've selected: \n\n" + year;
                        isDropdown_datesOpen = false;
                    }

                }
                else  if (isDropdown_OutputOpen) {
                    ///CLOCK STARTING
//                    auto startTime=chrono::high_resolution_clock::now();
                    auto startTime = chrono::steady_clock::now(); // begins timer when output dropdown pressed


                    if (option1_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        outputOption = 1;
                        //cout << "OUTPUT 1" << tree.getYear() << tree.getCategory() << endl;
                        vector<Node> treeNodes = tree.search(tree.getYear(), tree.getCategory());
                        vector<Node> tableNodes = table.search(table.getCategory(), table.getYear());
                        if(usingTree){
                            output = tree.displayOutput(treeNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice selected
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for tree: " << totalTime << endl;
                            isOutput_select=true;

                            // output time to screen in milliseconds using first three non-zero digits?
//                            cout << "in milliseconds" << int(totalTime * 10) << (totalTime * 100) % 10 << (totalTime * 1000) % 10 << endl;

                        }

                        else if(usingTable){
                            output = table.displayOutput(tableNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for table: " << totalTime << endl;
                            isOutput_select=true;
                        }
                        chosenType = "You've selected: \n\nAll info";
                        isDropdown_OutputOpen = false;
                    } else if (option2_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        outputOption = 2;
                        //cout << "OUTPUT 2" << endl;
                        vector<Node> treeNodes = tree.search(tree.getYear(), tree.getCategory());
                        vector<Node> tableNodes = table.search(table.getCategory(), table.getYear());
                        if(usingTree){
                            output = tree.displayOutput(treeNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for tree: " << totalTime << endl;
                            isOutput_select=true;

                        }

                        else if(usingTable){
                            output = table.displayOutput(tableNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for table: " << totalTime << endl;
                            isOutput_select=true;

                        }
                        chosenType = "You've selected: \n\nDates";
                        isDropdown_OutputOpen = false;
                    }
                    else if (option3_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        outputOption = 3;
                        //cout << "OUTPUT 3" << endl;
                        vector<Node> treeNodes = tree.search(tree.getYear(), tree.getCategory());
                        vector<Node> tableNodes = table.search(table.getCategory(), table.getYear());
                        if(usingTree){
                            output = tree.displayOutput(treeNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for tree: " << totalTime << endl;
                            isOutput_select=true;

                        }

                        else if(usingTable){
                            output = table.displayOutput(tableNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for table: " << totalTime << endl;
                            isOutput_select=true;

                        }
                        chosenType = "You've selected: \n\nProduct Names";
                        isDropdown_OutputOpen = false;
                    }
                    else if (option4_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        outputOption = 4;
                        //cout << "OUTPUT 4" << endl;
                        vector<Node> treeNodes = tree.search(tree.getYear(), tree.getCategory());
                        vector<Node> tableNodes = table.search(table.getCategory(), table.getYear());
                        /*if(usingBoth){
                            // USE BOTH

                        }*/
                        if(usingTree){
                            output = tree.displayOutput(treeNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // time in milliseconds
                            cout << "elapsed time for tree: " << totalTime << endl;
                            isOutput_select=true;

                        }

                        else if(usingTable){
                            output = table.displayOutput(tableNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end timer after choice is made
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // represent time in milliseconds
                            cout << "elapsed time for table: " << totalTime << endl;
                            isOutput_select=true;
                        }
                        chosenType = "You've selected: \n\nSymptoms";
                        isDropdown_OutputOpen = false;
                    }
                    else if (option5_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        outputOption = 5;
                        //cout << "OUTPUT 5" << endl;
                        vector<Node> treeNodes = tree.search(tree.getYear(), tree.getCategory());
                        vector<Node> tableNodes = table.search(table.getCategory(), table.getYear());
                        if(usingTree){
                            output = tree.displayOutput(treeNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // represent time in milliseconds
                            cout << "elapsed time for tree: " << totalTime << endl;
                            isOutput_select=true;


                        }

                        else if(usingTable){
                            output = table.displayOutput(tableNodes, outputOption);
//                            auto elapsedTime=chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now()-startTime).count();
                            auto endTime = chrono::steady_clock::now(); // end time after choice is made
                            float elapsedTime = chrono::duration_cast<chrono::duration<float>>(endTime - startTime).count();
                            totalTime = 1000*elapsedTime; // represent time in milliseconds
                            cout << "elapsed time for table: " << totalTime << endl;
                            isOutput_select=true;

                        }

                        chosenType = "You've selected: \n\nNumber of Cases";
                        isDropdown_OutputOpen = false;

                    }


                }
                else  if (isDropdown_StructureOpen) {
                    if (option1_structure.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        chosenStructure= "You've selected: \n\n20-ary Tree";
                        usingTree = true;
                        isDropdown_StructureOpen = false;
                    } else if (option2_structure.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        chosenStructure= "You've selected: \n\nHash Table";
                        usingTable = true;
                        isDropdown_StructureOpen = false;
                    }
                    else if (option3_output.getGlobalBounds().contains(static_cast<sf::Vector2f>(coordinate))) {
                        chosenStructure= "You've selected: \n\nBoth Structures";
                        usingBoth = true;
                        isDropdown_StructureOpen = false;
                    }


                }

            }

        }

        // Clear the window
        window.clear(sf::Color(255, 255, 230, 255));

        //DISPLAYS CLOCK TIME ONLY AFTER OUTPUT OPTION SELECTED FOR EACH LOOP
        if (isOutput_select==true){
            string time = "Time: " + to_string(totalTime) +" milliseconds";
            time_text.setString(time);
            sf::FloatRect textRect_time = time_text.getLocalBounds();
            time_text.setOrigin(textRect_time.left + textRect_time.width / 2.0f, textRect_time.top + textRect_time.height / 2.0f);
            time_text.setPosition(sf::Vector2f(1000/2.0f-100, 400/2.0f -100));
        }

        // draw all objects onto screen
        window.draw(time_text);
        window.draw(welcomeText);

        window.draw(dropdownButton);
        window.draw(dropDown1);

        //dates
        window.draw(dropdownButton_dates);
        window.draw(dropDown1_dates);

        window.draw(dropdownButton_output);
        window.draw(dropDown1_output);

        outputText.setString(output);
        sf::FloatRect textRect = outputText.getLocalBounds();
       // outputText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        outputText.setOrigin(400, 120);
        outputText.setPosition(sf::Vector2f(800/2.0f, 800/2.0f - 45));
        window.draw(outputText);

        selectedYear.setString(chosenYear);
        sf::FloatRect textRect1 = selectedYear.getLocalBounds();
        selectedYear.setOrigin(textRect1.left + textRect1.width / 2.0f, textRect1.top + textRect1.height / 2.0f);
        selectedYear.setPosition(sf::Vector2f(550/2.0f, 450/2.0f - 45));
        window.draw(selectedYear);


        selectedCat.setString(chosenCat);
        sf::FloatRect textRect2 = selectedCat.getLocalBounds();
        selectedCat.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
        selectedCat.setPosition(sf::Vector2f(950/2.0f, 450/2.0f - 45));
        window.draw(selectedCat);

        selectedType.setString(chosenType);
        sf::FloatRect textRect3 = selectedType.getLocalBounds();
        selectedType.setOrigin(textRect3.left + textRect3.width / 2.0f, textRect3.top + textRect3.height / 2.0f);
        selectedType.setPosition(sf::Vector2f(1350/2.0f, 450/2.0f - 45));
        window.draw(selectedType);

        selectedStructure.setString(chosenStructure);
        sf::FloatRect textRect4 = selectedStructure.getLocalBounds();
        selectedStructure.setOrigin(textRect4.left + textRect4.width / 2.0f, textRect4.top + textRect4.height / 2.0f);
        selectedStructure.setPosition(sf::Vector2f(200/2.0f, 450/2.0f - 45));
        window.draw(selectedStructure);

        content.setPosition(0, -scrollPosition);
        //window.draw(scrollBar);
       // window.draw(content);

        // Draw the dropdown options if the dropdown is open
        if (isDropdown_catOpen) {
            window.draw(option1);
            window.draw(option2);
            window.draw(textOption1);
            window.draw(textOption2);

            window.draw(option3);
            window.draw(option4);
            window.draw(textOption3);
            window.draw(textOption4);

            window.draw(option5);
            window.draw(option6);
            window.draw(textOption5);
            window.draw(textOption6);

            window.draw(option7);
            window.draw(option8);
            window.draw(textOption7);
            window.draw(textOption8);

            window.draw(option9);
            window.draw(option10);
            window.draw(textOption9);
            window.draw(textOption10);
        }
        if (isDropdown_datesOpen){
            window.draw(option1_dates);
            window.draw(option2_dates);
            window.draw(textOption1_dates);
            window.draw(textOption2_dates);

            window.draw(option3_dates);
            window.draw(option4_dates);
            window.draw(textOption3_dates);
            window.draw(textOption4_dates);

            window.draw(option5_dates);
            window.draw(option6_dates);
            window.draw(textOption5_dates);
            window.draw(textOption6_dates);

            window.draw(option7_dates);
            window.draw(option8_dates);
            window.draw(textOption7_dates);
            window.draw(textOption8_dates);

            window.draw(option9_dates);
            window.draw(option10_dates);
            window.draw(textOption9_dates);
            window.draw(textOption10_dates);
        }
        if (isDropdown_OutputOpen){
            window.draw(option1_output);
            window.draw(option2_output);
            window.draw(textOption1_output);
            window.draw(textOption2_output);

            window.draw(option3_output);
            window.draw(option4_output);
            window.draw(textOption3_output);
            window.draw(textOption4_output);

            window.draw(option5_output);
            window.draw(textOption5_output);

        }
        window.draw(dropdownButton_structure);
        window.draw(dropDown1_structure);
        if (isDropdown_StructureOpen){
            window.draw(option1_structure);
            window.draw(option2_structure);
            window.draw(textOption1_structure);
            window.draw(textOption2_structure);

        }


        // Display the contents of the window
        window.display();
    }
    return 0;
}

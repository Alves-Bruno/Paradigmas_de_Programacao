//
//  main.cpp
//  gerador_de_aplicacao
//
//  Created by Bruno Alves on 24/06/17.
//  Copyright © 2017 Bruno Alves. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <thread>
#include <fstream>
#include <sstream>
#include <mutex>          // std::mutex
#include <string>

void delSpaces(std::string &str)
{
   str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
}

class CSV {
    
private:
    
//    | Comando | Tipo | Label | Nome |

    std::string Command;
    std::string Type;
    std::string Label;
    std::string Name;
    
public:
    
    CSV(std::string Command, std::string Type, std::string Label, std::string Name){
   
        this->Command = Command;
        this->Type = Type;
        this->Label = Label;
        this->Name = Name;
    }
    
    std::string getCommand(){
        return Command;
    }
    
    std::string getType(){
        return Type;
    }
    
    std::string getLabel(){
        return Label;
    }
    
    std::string getName(){
        return Name;
    }
    
    
};


// todo -->> metodo para liberar memoria
class CSV_Editor {

private:
    
    std::vector<CSV*> CSVvector;
    std::ofstream CSV_file;
    int Total_lines = 0;
    
public:
    

    void free( void ){


    }


     void insert_line(std::string Command, std::string Type, std::string Label, std::string Name){
        CSV *csvType = new CSV(Command, Type, Label, Name);
        CSVvector.push_back(csvType);
        Total_lines++;
    }
    
    void list_commands( void ){
        int count = 1;
        for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
            //CSV *teste = i;
            std::cout<< "+  " << count << ". {" << (*i)->getCommand() << ", " << (*i)->getType()<< ", " << (*i)->getLabel()<< ", " << (*i)->getName() << '}' << std::endl;
            count++;
        }
    }

    void delete_line(int line_number){
        
        if(line_isValid(line_number) == false)
            return;
        
        delete CSVvector[line_number-1];
        CSVvector.erase(CSVvector.begin()+(line_number-1));
        
    
    }
    
    void edit_entire_line(int line_number, std::string Command, std::string Type, std::string Label, std::string Name){
        
        if(line_isValid(line_number) == false)
            return;
        CSV *csvType = new CSV(Command, Type, Label, Name);
        delete_line(line_number);
        CSVvector.insert(CSVvector.begin() + (line_number-1), csvType);
        
    
    }
    
    void edit_line_element(int line_number, int element, std::string new_element){
        
        if(line_isValid(line_number) == false)
            return;
        
        switch(element){
        
            case 1: edit_entire_line(line_number, new_element, CSVvector.at(line_number-1)->getType(), CSVvector.at(line_number-1)->getLabel(), CSVvector.at(line_number-1)->getName()); break;
            case 2: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), new_element, CSVvector.at(line_number-1)->getLabel(), CSVvector.at(line_number-1)->getName()); break;
            case 3: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), CSVvector.at(line_number-1)->getType(), new_element, CSVvector.at(line_number-1)->getName()); break;
            case 4: edit_entire_line(line_number,CSVvector.at(line_number-1)->getCommand(), CSVvector.at(line_number-1)->getType(), CSVvector.at(line_number-1)->getLabel(), new_element); break;
            default: std::cout << "ERROR: Invalid element number. Operation could not be done."  << std::endl;
            
        }
    }

    std::string get_PageTitle( void ){

    	return CSVvector.at(2)->getName();

    }
    
    std::string get_WebPage_name( void ){

      	return CSVvector.at(1)->getName();

     }

    bool line_isValid(int line_number){
        
        if((line_number-1) < 0 || (line_number-1) > CSVvector.size()){
            std::cout << "ERROR: Invalid line number. Operation in [line " << line_number << "] could not be done."  << std::endl;
            return false;
        } else return true;
    
    }
    
    bool save_project(std::string file_name){

    	CSV_file.open(file_name.data());
    	if(!CSV_file.is_open()){
    		return false;
    	}

    	for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
    		//CSV *teste = i;
    		CSV_file << (*i)->getCommand() << "," << (*i)->getType()<< "," << (*i)->getLabel()<< "," << (*i)->getName() << std::endl;

    	}

    	CSV_file.close();
    	return true;
    }

    bool load_project(std::string file_name){

    	//todo verificar se arquivo está correto.
    	//todo salvar nome do projeto e nome do arquivo

    	std::ifstream data(file_name.data());

    	std::string line;
    	std::string cell[4];

    	while (std::getline(data, line)) {
    		std::stringstream linestream(line);
    		std::getline(linestream, cell[0], ',');
    		std::getline(linestream, cell[1], ',');
    		std::getline(linestream, cell[2], ',');
    		std::getline(linestream, cell[3], ',');
    		CSV *linha = new CSV(cell[0], cell[1] ,cell[2], cell[3]);
    		CSVvector.push_back(linha);
    	}


    }

    CSV* get_line(int line_number){

    	return CSVvector.at(line_number-1);
    }

    
    

};


//todo -->> metodo para liberar memória
class Application {

   	 private:

		std::string project_name;
		std::string project_file;
		std::string code_file;
		CSV_Editor *CSV_editor;

    public:

	std::mutex mtx;

    Application(){
    	this->CSV_editor = new CSV_Editor();
    	this->project_file = "";
    	this->project_name = "";
    	this->code_file = "";
    }

//	void generate_code();

    void new_project(std::string project_name, std::string project_file){

    	this->project_name = project_name;
    	this->project_file = project_file;
    	CSV_editor->insert_line("project_title", "text",project_file, project_name);
    	CSV_editor->insert_line("set", "text","web_page_name", "");
    	CSV_editor->insert_line("set", "text","page_title", "");
    	this->save_project();
    }

    bool load_project(std::string project_file_name){


    	CSV_editor->load_project(project_file_name);
    	CSV *title = CSV_editor->get_line(1);
    	this->project_name = title->getName();
    	this->project_file = title->getLabel();


    }
    bool save_project(void){
    	return CSV_editor->save_project(this->project_file);
    }

    CSV_Editor* get_CSVeditor( void ){

    	return this->CSV_editor;
    }

    std::string get_ProjectName(void){
    	return this->project_name;
    }

    std::string get_ProjectFile(void){
        	return this->project_file;
     }
};

class Radio {

private:

	std::string Label;
	std::string Name;
	std::vector<std::string> Radio_buttons;

public:

	Radio(std::string Label, std::string Name){

		this->Label = Label;
		this->Name = Name;

	}
	std::string getLabel( void ){
		return Label;
	}

	std::string getName( void ){
			return Name;
	}

	void insert_RadioButton( std::string button ){

		Radio_buttons.push_back(button);
	}

	std::vector<std::string> Get_Radio_buttons( void ){

		return Radio_buttons;
	}


};

// todo -->> metodo para liberar memoria
class Code_Generator {

private:

	std::string project_title;
	std::string web_page_name;
	std::vector<CSV*> adds;
	std::string snippets[7];

    std::vector<CSV*> CSVvector;
    std::ofstream CSV_file;
    std::ofstream HTML_file;

    std::vector<Radio*> Radio_adds;


public:

    Code_Generator(std::string project_title, std::string web_page_name, std::string CSV_file_name){

    	this->snippets[0] = "<!--DO NOT EDIT THIS FILE BY HAND-->\n"
    			"<!DOCTYPE html>\n"
    			"<html lang=\"en\">\n"
    			"<head>\n"
    			"    <meta charset=\"utf-8\">\n"
    			"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
    			"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";


    	this->snippets[1] = "    <link href=\"css/bootstrap.min.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery-1.11.1.min.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/bootstrap-3.1.1.min.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.validationEngine-2.6.2.js\"></script>\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.validationEngine-en.js\"></script>\n"
    			"    <link href=\"css/validationEngine.jquery.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"    <script language=\"JavaScript\" type=\"text/javascript\" src=\"js/jquery.dataTables-1.10.0.min.js\"></script>\n"
    			"    <link href=\"css/jquery.dataTables.min.css\" rel=\"stylesheet\" media=\"screen\">\n"
    			"</head>\n"
    			"<body>\n"
    			"    <div class=\"container\">\n";

    	this-> snippets[2] = "    \t<div id=\"list\">\n"
    			"    \t\t<table id=\"table\" class=\"display\"></table>\n"
    			"    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<button type=\"submit\" class=\"submit btn btn-primary\" id=\"add\">Add</button>\n"
    			"    \t\t</div>\n"
    			"\t    </div>\n"
    			"    \t<form class=\"form-horizontal\" role=\"form\" id=\"formID\">\n"
    			"    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<label for=\"seq\" class=\"col-sm-2 control-label\">Id</label>\n"
    			"    \t\t\t<div class=\"col-sm-6\">\n"
    			"    \t\t\t\t<p class=\"form-control-static\" id=\"seq\"></p>\n"
    			"    \t\t\t</div>\n"
    			"    \t\t</div>\n";

    	this-> snippets[3] = "    \t\t<div class=\"form-group\">\n"
    			"    \t\t\t<div class=\"col-sm-offset-2 col-sm-8\">\n"
    			"    \t\t\t\t<button class=\"btn btn-default\" id=\"cancel\">Cancel</button>\n"
    			"    \t\t\t\t<button type=\"submit\" class=\"submit btn btn-primary\" id=\"save\">Save</button>\n"
    			"    \t\t\t</div>\n"
    			"    \t\t</div>\n"
    			"    \t</form>\n"
    			"\t</div>\n"
    			"</body>\n"
    			"<script>\n"
    			"\tvar editor; // use a global for the submit and return data rendering in the examples\n"
    			"\tvar formId=\"sample\";\n"
    			"\tvar oTable;\n"
    			"\t$(document).ready(function(){\n"
    			"\t\t$('#formID').hide();\n"
    			"\t\tvar seq=createTable();\n"
    			"\t\t$('#seq').text(seq);\n"
    			"\t\t$(\"#formID\").validationEngine(\'attach\',\n"
    			"\t\t{\n"
    			"\t\t\tonValidationComplete: function(form, status){\n"
    			"\t\t\t\tif (!verifyLocalStorageCapability) {\n"
    			"\t\t\t\t\talert(\"Local Storage is not supported.\");\n"
    			"\t\t\t\t\treturn;\n"
    			"\t\t\t\t}\n"
    			"\t\t\t\tif (status) {\n"
    			"\t\t\t\t\tsave();\n"
    			"\t\t\t\t\tlocation.reload(true);\n"
    			"\t\t\t\t}\n"
    			"\t\t\t}\n"
    			"\t\t});\n"
    			"\t});\n"
    			"\n"
    			"\tfunction createTable() {\n"
    			"\t\tvar dataSet=[];\n"
    			"\t\tvar skip=0;\n"
    			"\t\tvar seq=0;\n"
    			"\t\tvar index=0;\n"
    			"\t\tvar icons  =\'<span class=\"glyphicon glyphicon-edit\">&nbsp;</span><span class=\"glyphicon glyphicon-remove\"></span>\';\n"
    			"\n"
    			"\t\twhile ( skip<2 ) {\n"
    			"\t\t\tvar key=formId+\"_\"+index;\n"
    			"\t\t\tvar json=localStorage.getItem(key);\n"
    			"\t\t\tif ( json==null || json==\"null\" || json==\"[object Object]\" ) {\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tskip=skip+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tvar object=null;\n"
    			"\t\t\tobject=JSON.parse(json);\n"
    			"//\t\t\tvar note= object.note;\n"
    			"//\t\t\tnote=note.replace(/\\n/g, \"<br>\");\n";

    	this->snippets[4] = 	"\t\t\tindex=index+1;\n"
    			"\t\t\tseq=seq+1;\n"
    			"\t\t}\n"
    			"\n"
    			"oTable=$('#table').dataTable({\n"
    			"\"data\": dataSet,\n"
    			"\"columns\": [\n"
    			"{ \"title\": \"Seq\", \"class\": \"center\" },\n"
    			"{ \"title\": \"\", \"class\": \"center\" },\n";

    	this->snippets[5] = "\t\t$('#table tbody').on( 'click', '.glyphicon-remove', function () {\n"
				"\t\t    var row = $(this).parents('tr');\n"
				"\t\t    var seq = row.children()[0].innerHTML;\n"
				"\t\t    if(window.confirm('Are you sure to delete? Seq='+seq)){\n"
				"\t\t    \tvar key=formId+\"_\"+seq;\n"
				"\t\t    \tlocalStorage.removeItem(key);\n"
				"\t\t    \trestoreItems();\n"
				"        \tlocation.reload(true);\n"
				"\t\t    }\n"
				"\t\t} );\n"
				"\n"
				"\t\t$('#add').on( 'click', function () {\n"
				"\t\t    $('#list').hide();\n"
				"\t\t    $('#seq').text(seq);\n"
				"\t\t    $('#formID').show();\n"
				"\t\t} );\n"
				"\n"
				"\t\t$('#cancel').on( 'click', function () {\n"
				"\t\t    location.reload(true);\n"
				"\t\t} );\n"
				"\n"
				"$('#table tbody').on( 'click', '.glyphicon-edit', function () {\n"
				"$('#list').hide();\n"
				"var rows = $(this).parents('tr').children();\n"
				"$('#seq').text(rows[0].innerHTML);\n";

    	this->snippets[6] =  "\tfunction restoreItems() {\n"
    			"\t\tvar skip=0;\n"
    			"\t\tvar index=1;\n"
    			"\t\tvar previous=JSON.parse(localStorage.getItem(formId+\"_0\"));\n"
    			"\t\tvar prevIndex=0;\n"
    			"\t\twhile ( skip<2 ) {\n"
    			"\t\t\tvar key=formId+\"_\"+index;\n"
    			"\t\t\tvar object=JSON.parse(localStorage.getItem(key));\n"
    			"\t\t\tif ( previous==null && object==null ) {\n"
    			"\t\t\t\tskip=skip+1;\n"
    			"\t\t\t\tprevIndex=index;\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tif ( previous==null && object!=null ) {\n"
    			"\t\t\t\tlocalStorage.setItem(formId+\"_\"+prevIndex, JSON.stringify(object));\n"
    			"\t\t\t\tlocalStorage.setItem(key, null);\n"
    			"\t\t\t\tprevIndex=index;\n"
    			"\t\t\t\tindex=index+1;\n"
    			"\t\t\t\tcontinue;\n"
    			"\t\t\t}\n"
    			"\t\t\tprevious=object;\n"
    			"\t\t\tprevIndex=index;\n"
    			"\t\t\tindex=index+1;\n"
    			"\t\t}\n"
    			"\t};\n"
    			"\n"
    			"\n"
    			"\tfunction verifyLocalStorageCapability() {\n"
    			"\t\tif (!window.localStorage) {\n"
    			"\t    \treturn false;\n"
    			"\t\t}\n"
    			"\t\treturn true;\n"
    			"\t}\n"
    			"</script>\n"
    			"</html>\n"
    			"\n";

    	this->project_title = project_title;
    	this->web_page_name = web_page_name;
    	this->load_project(CSV_file_name);
    	this->fill_adds();


    }

    // todo excessões
    void fill_adds( void ){

           for (auto i = (CSVvector.begin()+3); i != CSVvector.end(); i++){

        	   if ((*i)->getCommand() == "add" && (*i)->getType() == "text"){
            	   adds.push_back((*i));
               }

        	   if ((*i)->getCommand() == "add" && (*i)->getType() == "radio"){
            	   //adds.push_back((*i));

        		   Radio* button = new Radio((*i)->getLabel(), (*i)->getName());

        		   i++;
        		   while(i != CSVvector.end() && (*i)->getCommand() == "radio_bt"){

        			   if((*i)->getType() != "#null#"){
        				   button->insert_RadioButton((*i)->getType());
        			   }
        			   if((*i)->getLabel() != "#null#"){
        				   button->insert_RadioButton((*i)->getLabel());
        			   }
        			   if((*i)->getName() != "#null#"){
        				   button->insert_RadioButton((*i)->getName());
        			   }
        			   i++;
        		   }

        		   Radio_adds.push_back(button);
        		   i--;
               }
           }
    }

    bool write_code(){

    	HTML_file.open("HTML/index.html");
    	if(!HTML_file.is_open()){
    		return false;
    	}


    	//WEB PAGE NAME
    	HTML_file << snippets[0];
    	HTML_file << "<title>" << this->web_page_name << "</title>\n";

    	//PAGE TITLE
    	HTML_file << snippets[1];
    	HTML_file << "<h1>" << this->project_title << "</h1>\n";

    	//INSERT ADDS
    	HTML_file << snippets[2];

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "<div class=\"form-group\">\n";
    		HTML_file << "<label for=\"" << (*i)->getLabel() << "\" class=\"col-sm-2 control-label\">" << (*i)->getName() << "</label>\n";
    		HTML_file << "<div class=\"col-sm-6\">\n";
    		HTML_file << "<input type=\"" << (*i)->getType() << "\" class=\"form-control validate[required]\" id=\"" << (*i)->getLabel() << "\" placeholder=\"" << (*i)->getName() << "\">\n";
    		HTML_file << "</div>\n";
    		HTML_file << "</div>\n";

    	}

    	int rvar = 0;
      	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

//        		std::cout<< "RADIO(" << (*i)->getLabel() << ", " << (*i)->getName() << ")" << std::endl;
        		auto vec = (*i)->Get_Radio_buttons();

        	 	HTML_file << "    \t\t<div class=\"form-group\">\n";
        	 	HTML_file << "    \t\t\t<label for=\"" << (*i)->getLabel() << "\" class=\"col-sm-2 control-label\">" << (*i)->getName() << "</label>\n";

        	    HTML_file <<	"    \t\t\t<div class=\"col-sm-6\">\n";

        		for (auto a = vec.begin(); a != vec.end(); a++){

//        			std::cout << "\t" << (*a) << std::endl;

        			HTML_file << "\t    \t\t\t<div class=\"radio\">\n"
        		    	"\t    \t\t\t\t<label>\n";

        			std::string var;
        			var = (*a);
        			delSpaces(var);
        		    HTML_file <<	"\t    \t\t\t\t\t<input type=\"radio\" class=\"validate[required]\" name=\"" << (*i)->getLabel() << "\" value=\"" << var <<"\">\n"
        		    	"\t    \t\t\t\t\t" << (*a) << "\n";
        		    rvar++;

        		    HTML_file <<	"\t    \t\t\t\t</label>\n"
        		    	"\t    \t\t\t</div>\n";
        		}

        		HTML_file <<  "    \t\t\t</div>\n"
        		    	"    \t\t</div>\n";


        }

    	HTML_file << snippets[3];

    	HTML_file << "dataSet[seq]=[index, icons";
    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << ", object." << (*i)->getLabel();

        }

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << ", object." << (*i)->getLabel();

    	}

    	HTML_file << "];\n";

        HTML_file << snippets[4];

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "{ \"title\": \"" << (*i)->getName() << "\"},\n";

        }

        for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

        	HTML_file << "{ \"title\": \"" << (*i)->getName() << "\"},\n";
        }

        HTML_file << "]\n" << "});\n";

        HTML_file << snippets[5];

        int count = 2;
    	for (auto i = adds.begin(); i != adds.end(); i++){

        		HTML_file << "$('#" << (*i)->getLabel() << "').val(rows[" << count << "].innerHTML);\n";
        		count++;
         }

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << "$('input[name=\"" << (*i)->getLabel() << "\"]').val([rows[" << count << "].innerHTML]);\n";
    		count++;
    	}


    	HTML_file << "$('#formID').show();\n" << "} );\n" << "\n";


    	HTML_file << "\n"
    			"\t\treturn seq;\n"
    			"\t}\n"
    			"\n"
    			"function save() {\n"
				"  var seq=$('#seq').text();\n"
				"  if ( isNaN(seq) ) { seq=0; }\n"
				"  var key=formId+\"_\"+seq;\n"
				"  var object={\n";

    	for (auto i = adds.begin(); i != adds.end(); i++){

    		HTML_file << "\"" << (*i)->getLabel() << "\": $(\"#" << (*i)->getLabel() << "\").val(),\n";
    	}

    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){

    		HTML_file << "\"" << (*i)->getLabel() << "\": $('input[name=\"" << (*i)->getLabel() << "\"]:checked').val(),\n";
    	}


    	HTML_file << "}\n"
				"localStorage.setItem(key, JSON.stringify(object));\n"
				"}\n";


    	HTML_file << snippets[6];


    	HTML_file.close();
    	return true;

    }

    bool write_project(std::string file_name){

    	CSV_file.open(file_name.data());
    	if(!CSV_file.is_open()){
    		return false;
    	}

    	for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
    		//CSV *teste = i;
    		CSV_file << (*i)->getCommand() << "," << (*i)->getType()<< "," << (*i)->getLabel()<< "," << (*i)->getName() << std::endl;

    	}

    	CSV_file.close();
    	return true;
    }

//    void print_radio_adds( void ){
//
//    	for (auto i = Radio_adds.begin(); i != Radio_adds.end(); i++){
//
//    		std::cout<< "RADIO(" << (*i)->getLabel() << ", " << (*i)->getName() << ")" << std::endl;
//    		auto vec = (*i)->Get_Radio_buttons();
//
//    		for (auto a = vec.begin(); a != vec.end(); a++){
//
//    			std::cout << "\t" << (*a) << std::endl;
//    		}
//
//    	}
//    }


    //todo
//    void page_title_writer(line){
//
//
//    }


    bool load_project(std::string file_name){

    	//todo verificar se arquivo está correto.
    	//todo salvar nome do projeto e nome do arquivo

    	std::vector<CSV*> novo;
    	std::ifstream data(file_name.data());

    	std::string line;
    	std::string cell[4];

    	while (std::getline(data, line)) {
    		std::stringstream linestream(line);
    		std::getline(linestream, cell[0], ',');
    		std::getline(linestream, cell[1], ',');
    		std::getline(linestream, cell[2], ',');
    		std::getline(linestream, cell[3], ',');
    		CSV *linha = new CSV(cell[0], cell[1] ,cell[2], cell[3]);
    		novo.push_back(linha);
    		this->CSVvector = novo;
    	}


    }

};

void command_handler(std::vector<std::string> command, Application *app){

	switch(command.size()){

	case 1: {

		if(command[0] == "list"){
			(app->get_CSVeditor())->list_commands();
		}
		else if(command[0] == "quit" || command[0] == "q"){

			// todo -->> free mem app
			exit(0);
		}
		else if(command[0] == "info"){

			// todo -->> apresentar informações sobre o projeto
			std::cout << ">> In Project \"" << app->get_ProjectName() << "\", try \"help\" for more informations." << std::endl;
		}
		else if(command[0] == "help" || command[0] == "h"){

			std::cout << "Usage: ./main [options] or just ./main [to start a new project.]" << std::endl;
			std::cout << "Options:\n " << "\t file.csv \t To load a project" << std::endl;

			std::cout << "Commands inside of the program:\n"
					"\t\n"
					"\tset page\t--> Sets the web page name.\n"
					"\tset title\t--> Sets the web page title.\n"
					"\tlist\t\t--> List the commands, like an project view.\n"
					"\tinfo\t\t--> Displays some info about the project.\n"
					"\tquit\t\t--> Exit the program.\n"
					"\n"
					"\trm [line_number]\t\t\t--> Removes the line at [line_number].\n"
					"\tedit [line_number] [element_number]\t--> Edit the element at [element_number] in line indicated.\n"
					"\n"
					"\n"
					"\tadd text [labe] [Name]\t\t--> Adds a text box section in the web page.\n"
					"\tadd radio [label] [Name] \t--> Adds a radio button section in the web page.\n"
					"\tgenerate code \t--> Generates the html code.\n"
					"\n";
		}
		else {
			std::cout << "Command not found, try \"help\" for more information.\n";
		}

		break;
	}

	case 2:{

		if(command[0] == "set"){

			if(command[1] == "page"){

				char web_page_name[50];
				std::cout << "Enter the new web page name: ";
				std::cin.getline(web_page_name, 50);
				std::cout << std::endl;
				std::string str = web_page_name;
				(app->get_CSVeditor())->edit_line_element(2, 4, str);
			}
			else if(command[1] == "title"){
				char page_title[100];
				std::cout << "Enter the new page title: ";
				std::cin.getline(page_title, 100);
				std::cout << std::endl;
				std::string str = page_title;
				(app->get_CSVeditor())->edit_line_element(3, 4, str);
			}
		}
		else if(command[0] == "rm"){

			try {

				int line_number = std::stoi(command[1]);
				if (line_number == 1 || line_number == 2 || line_number == 3){
					std::cout << "Error: It is not permitted to delete lines 1, 2, 3." << std::endl;
					return;
				}
				(app->get_CSVeditor())->delete_line(line_number);

			} catch (const std::invalid_argument& ia) {
				  std::cout << "Error: line_number is invalid. Operation could not be done." << std::endl;
			}
		}

		else if(command[0] == "generate" && command[1] == "code"){

			Code_Generator codigo((app->get_CSVeditor())->get_PageTitle(), (app->get_CSVeditor())->get_WebPage_name(), app->get_ProjectFile());
			codigo.write_code();

		}
		else {
			std::cout << "Command not found, try \"help\" for more information.\n";
		}
		break;
	}

	case 3:{

		if(command[0] == "edit"){

			try {

				int line_number = std::stoi(command[1]);
				int element = std::stoi(command[2]);
				if (line_number == 1 || line_number == 2 || line_number == 3){
					std::cout << "Error: It is not permitted to edit lines 1, 2, 3. Try \"set\" modes." << std::endl;
					return;
				}

				char element_char[100];
				std::cout << "Enter the element (string) to be overwritten: ";
				std::cin.getline(element_char, 100);
				std::cout << std::endl;
				std::string str = element_char;

				(app->get_CSVeditor())->edit_line_element(line_number, element, str);

			} catch (const std::invalid_argument& ia) {
				std::cout << "Error: line_number is invalid. Operation could not be done." << std::endl;
			}

		}
		else {
					std::cout << "Command not found, try \"help\" for more information.\n";
				}
		break;
	}

	case 4: {

		if(command[0] == "add" && command[1] == "text"){

			(app->get_CSVeditor())->insert_line("add", "text", command[2], command[3]);
		}

		else if(command[0] == "add" && command[1] == "radio"){

			char num_char[20];
			(app->get_CSVeditor())->insert_line("add", "radio", command[2], command[3]);
			std::cout << "Enter the number of radio buttons to insert: ";
			std::cin.getline(num_char, 20);
			std::cout << std::endl;
			std::string num_str = num_char;
			int num_bt = std::stoi(num_str);

			for(int i = 0; i < num_bt; i++){

				char element_char[100];
				std::cout << "Enter the" << (i+1) <<"º radio button name: ";
				std::cin.getline(element_char, 100);
				std::cout << std::endl;
				std::string radio_bt = element_char;
				(app->get_CSVeditor())->insert_line("radio_bt", radio_bt, "#null#", "#null#");
			}

		}
		else {
					std::cout << "Command not found, try \"help\" for more information.\n";
		}
	}

	}

}

int main_loop(Application *app){

	char command[256];



	while(1){

		std::cout << ">> ";
		std::cin.getline(command, 256);
//		std::cout << command;

		std::string command_str = command, buf;
		std::vector<std::string> command_vector;
		std::stringstream ss(command_str);


	    while (ss >> buf){
	        command_vector.push_back(buf);
	    }

	    command_handler(command_vector, app);
	    app->save_project();

	}
}

int main(int argc, const char * argv[]) {
   
	char name[256];

	Application *app = new Application();
	if(argc == 1){
		std::cout << ">> New Project name: ";
		std::cin.getline(name, 256);
		std::string project_name = name;
		std::cout << ">> File to save project: ";
		std::cin.getline(name, 256);
		std::string project_file = name;

		app->new_project(project_name, project_file);

	}
	if(argc == 2){

		std::string project_name = argv[1];
		app->load_project(project_name);
		std::cout << ">> In Project \"" << app->get_ProjectName() << "\", file loaded: OK." << std::endl;
//		(app->get_CSVeditor())->list_commands();
	}

	std::thread thread_loop (main_loop, app);
	thread_loop.join();


    
    return 0;
}

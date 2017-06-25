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

class CSV_Editor{

private:
    
    std::vector<CSV*> CSVvector;
    
public:
    
    void insert_line(std::string Command, std::string Type, std::string Label, std::string Name){
        CSV *csvType = new CSV(Command, Type, Label, Name);
        CSVvector.push_back(csvType);
    }
    
    void list_commands( void ){
        int count = 1;
        for (auto i = CSVvector.begin(); i != CSVvector.end(); i++){
            //CSV *teste = i;
            std::cout<< count << ". {" << (*i)->getCommand() << ", " << (*i)->getType()<< ", " << (*i)->getLabel()<< ", " << (*i)->getName() << '}' << std::endl;
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
    
    bool line_isValid(int line_number){
        
        if((line_number-1) < 0 || (line_number-1) > CSVvector.size()){
            std::cout << "ERROR: Invalid line number. Operation in [line " << line_number << "] could not be done."  << std::endl;
            return false;
        } else return true;
    
    }
    
    
    

};

class Application {

    public:

    
    private:
    
    void generate_code();
    void new_project();
    void load_project();
    void save_project();
};

int main(int argc, const char * argv[]) {
   
    CSV_Editor editor;
    
    editor.insert_line("add", "text", "var", "var");
    editor.insert_line("add2", "text2", "var2", "var2");
    editor.insert_line("add3", "text3", "var3", "var3");
    editor.list_commands();
    editor.edit_line_element(2, 0, "ABACATE");
    editor.delete_line(10);
    std::cout << "------------" << std::endl;
    editor.list_commands();
    
    return 0;
}

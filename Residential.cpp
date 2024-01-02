#include "Residential.h"

Persons Per; // access the persons class functions

int totalPop(vector<vector<struct Cell> > &c){ //simple total pop func
    int pop = 0;
    for (int i = 0; i < c.size(); i++)
        for (int j = 0; j < c[i].size(); j++){
            pop+=c[i][j].population; //for each iteration add the population
        }
    return pop;
}


int getAdj(vector<vector<struct Cell> > &c, int w, int x) {//get adj cells for cell w/ pop ranges between 1-2 & looks with city
    int pop = 0;

    if(w > 0){pop+=c[w-1][x].population;}
    if(w+1 < 3){pop+=c[w+1][x].population;} //adding up the pop of the adj cells
    if(x > 0){pop+=c[w][x-1].population;}
    if(x+1 < 3){pop+=c[w][x+1].population;}

    return pop;
}

int getAdj3P4(vector<vector<struct Cell> > &c, int w) {//get adj cells for cell pop of 3-4 & looks at reslist rather than city
    int pop = 0;
    int count = 0;
    for (int i = 0; i < c.size(); i++)
        for (int j = 0; j < c[i].size(); j++){
            pop+=c[i][j].population;
            if(w == count){
                return pop;
            }
        }

    return pop;
}

void popSize0(vector<vector<struct Cell> > &c, int &pop){ //for cells with pop == 0
    for (int i = 0; i < c.size(); i++)
        for (int j = 0; j < c[i].size(); j++){
            if(c[i][j].cell_type == 'R' && c[i][j].population == 0 && !c[i][j].updated_this_step) {
                if (c[i][j].next_to_power) {
                    c[i][j].population++;
                    c[i][j].updated_this_step = true;
                    pop++;
                    Per.addPerson(c[i][j].cell_position); //create a person in this specific cell
                } else if (c[i][j].adjacent_cell_population == 1) {
                    c[i][j].population++;
                    c[i][j].updated_this_step = true;
                    pop++;
                    Per.addPerson(c[i][j].cell_position); //create a person in this specific cell
                }
            }
        }

    return;
}

void popSize1To4(vector<vector<struct Cell> > &cc, int &unemp,int &pop) {
    int count = 0; //track iteration and which R cell in whole state we are in
    bool cont = false; //allow pop inc
    for (int i = 0; i < cc.size(); i++)
        for (int j = 0; j < cc[i].size(); j++){ //iterate the list
            if (cc[i][j].cell_type != 'R') continue;
            for (int k = 4; k >= 0; k--)
            {
                if (cc[i][j].population != k) continue;
                
                for (int l = 32; l >= (2*k*k); l--){
                    if (cc[i][j].adjacent_cell_population == l && l != 0 && cc[i][j].adjacent_cells_equal_pop >= (cc[i][j].population * 2)){
                        cc[i][j].population++;
                        cc[i][j].updated_this_step = true;
                        pop++;
                        unemp++;
                        Per.addPerson(cc[i][j].cell_position);
                        cont = false;
                    }
                }
                
                if (cc[i][j].population == 0 && cc[i][j].next_to_power) {
                    cc[i][j].population++;
                    cc[i][j].updated_this_step = true;
                    pop++;
                    unemp++;
                    Per.addPerson(cc[i][j].cell_position); //create a person in this specific cell
                }
            }
        }
    
    return; //return new state residential list
}
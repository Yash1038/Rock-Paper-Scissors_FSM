#include<bits/stdc++.h>

#define ll long long int
#define ff(i,a,b) for(int i=a;i<b;i++)
#define fr(i,a,b) for(int i=a;i>=b;i--)
#define pii pair<int,int>

using namespace std;

vector<vector<int>> input;
vector<vector<int>> output;
string S = "RPS";

int qualifier(int a, int b){
    if((a == 0 && b == 1 )|| (a==1 && b==2) || (a==2 && b == 0)){
        return 1;
    }
    return 0;
}

int main(){
    int n;
    cin >> n;
    int flag1 = 0,flag2 = 0,flag3 = 0;
    int r1=0,r2=0,r3=0,p1=0,p2=0,p3=0,s1=0,s2=0,s3=0;
    vector<vector<int>> max;
    max.resize(6);
    ff(i,0,6){
        max[i].resize(n+1,0);
    }

    ff(i,0,n){
        char c;
        cin >> c;
        int x,y,z;
        cin >> x >> y >> z;
        int a;
        if(c == 'R'){
            a = 0;
            flag1 = 1;
            max[0][x]++;
            max[1][z]++;
            if(max[0][x] > max[0][r1])r1=x;
            if(max[1][z] > max[1][r3])r3=z;
        } 
        if(c == 'P'){
            a = 1;
            flag2 = 1;
            max[2][x]++;
            max[3][y]++;
            if(max[2][x] > max[2][p1])p1=x;
            if(max[3][y] > max[3][p2])p2=y;
        } 
        if(c == 'S'){
            a = 2;
            flag3 = 1;
            max[4][y]++;
            max[5][z]++;
            if(max[4][y] > max[4][s2])s2=y;
            if(max[5][z] > max[5][s3])s3=z;
        } 
        
        input.push_back({a,x,y,z});
    }

    srand(time(NULL));

    ff(i,0,n){
        int temp = (input[i][0] + 1)%3;
        int r,p,s;
        if(input[i][0]==0){
            r = input[i][2];
            if(flag2 == 0){
                p=(rand() % n) + 1;
            }
            else{
                p = p2;
            } 

            if(flag3 == 0){
                s=(rand() % n) + 1;
            }
            else {
                s = s2;
            }
        }else if(input[i][0] == 1){
            p = input[i][3];
            if(flag1 == 0){
                r=(rand() % n) + 1;
            }
            else {
                r = r3;
            }

            if(flag3 == 0){
                s=(rand() % n) + 1;
            }
            else{
                s = s3;
            }
        }else{
            s = input[i][1];
            if(flag1==0){
                r=(rand() % n) + 1;
            }    
            else{
                r = r1;
            } 

            if(flag2==0){
                p=(rand() % n) + 1;
            }    
            else {
                p = p1;
            }    
        }
        output.push_back({temp,r,p,s});
    }


    // Simulation
    int checker = 1;
    int eval = 0;

    ff(i,1,n){
        int my_state = 0;
        int opp_state = i;
        int my_prev_state = 0;
        int opp_prev_state = opp_state;
        opp_state = input[opp_prev_state][output[my_prev_state][0] + 1] - 1;
        my_state = output[my_prev_state][input[opp_prev_state][0] + 1] - 1;
        //cout << my_state << " " << opp_state << endl;
        ff(j,0,100){
            if(my_state == opp_state){
                break;
            }
            int x = input[opp_prev_state][0];
            int y = output[my_prev_state][0];
            if((my_state != opp_state) && (qualifier(x,y) == 0)){
                eval++;
                //cout << eval;
            }
            if(eval == checker){
                eval = 0;
                checker++;
                output[my_prev_state][input[opp_prev_state][0] + 1] = input[opp_prev_state][output[my_prev_state][0] + 1];
                //cout << output[my_state][input[opp_state][0] + 1] << endl;
                break;
            }
            my_prev_state = my_state;
            opp_prev_state = opp_state;
            opp_state = input[opp_prev_state][output[my_prev_state][0] + 1] - 1; 
            my_state = output[my_prev_state][input[opp_prev_state][0] + 1] - 1;
        }
    }


    cout << n << endl;
    ff(i,0,n){
        cout << S[output[i][0]] << " " << output[i][1] << " " << output[i][2] << " " << output[i][3] << endl;
    }

    return 0;
}
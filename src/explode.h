

    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdlib.h>
    using namespace std;
    vector<string> explode(string str, string del)
    {
    	int slen = str.length();
    	int dlen = del.length();
    	int found_a;
    	string before;
    	vector<string> final;
    	vector<string> fail (0);
    	if(dlen == 0) return fail;
    	if(slen == 0) return fail;
    	for(int counter = 0; counter < slen; counter ++)
    	{
    		found_a = str.find(del);
    		if(found_a != string::npos)
    		{
    			before = str.substr(0, found_a + dlen);
    			final.push_back(before);
    			str.replace(0, found_a + dlen, "");
    		}
    		else
    		{
    			if(str.length() > 0)
    			{
    				final.push_back(str);
    				str.replace(0, str.length(), "");
    			}
    			else
    			{
    				break;
    			}
    		}
    	}
    	return final;
    }


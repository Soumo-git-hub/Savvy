#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // for std::sort 
#include <map>
#include <limits> 
#include <cmath>  
using namespace std;

// A class to represent a laptop model
class Laptop
{
public:
    // Attributes of the laptop
    string name;
    string brand;
    double price;
    string processor;
    string processorBrand; 
    int cores;             
    int ram;
    int storage;
    int battery;
    double screen;
    double weight;
    string graphicsCard;
    bool powerUser;  // Added suitability for power users
    bool generalUse; // Added suitability for general users
    bool lightTasks; // Added suitability for light tasks

    // Constructor with updated parameter list
    Laptop(string n, string b, double p, string pr, string pb, int c, int r, int s, int ba, double sc, double w, string gc, bool pu, bool gu, bool lt) : name(n), brand(b), price(p), processor(pr), processorBrand(pb), cores(c), ram(r), storage(s), battery(ba), screen(sc), weight(w), graphicsCard(gc), powerUser(pu), generalUse(gu), lightTasks(lt) {}

    // A method to display the details of the laptop
    void display() const
    {
        cout << "Name: " << name << endl;
        cout << "Brand: " << brand << endl;
        cout << "Price: ₹" << convertToINR(price) << endl; // Display price in Indian Rupees
        cout << "Processor: " << processor << endl;
        cout << "Processor Brand: " << processorBrand << endl; 
        cout << "Number of Cores: " << cores << endl;          
        cout << "RAM: " << ram << " GB" << endl;
        cout << "Storage: " << storage << " GB" << endl;
        cout << "Battery: " << battery << " Wh" << endl;
        cout << "Screen: " << screen << " inches" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << "Graphics Card: " << graphicsCard << endl;
        cout << "Suitability:" << endl;
        cout << "  For Power Users: " << (powerUser ? "Yes" : "No") << endl;  // Display suitability for power users
        cout << "  For General Use: " << (generalUse ? "Yes" : "No") << endl; // Display suitability for general users
        cout << "  For Light Tasks: " << (lightTasks ? "Yes" : "No") << endl; // Display suitability for light tasks
    }

    double convertToINR(double priceInDollars) const
    {
        // Current exchange rate: 1 USD = 83.3 INR 
        return priceInDollars * 83.3;
    }

    // Method to scale price by a factor
    void scalePrice(double scalingFactor)
    {
        price *= scalingFactor;
    }

    // Method to calculate similarity score between two laptops
    double calculateSimilarityScore(const Laptop &other) const
    {
        // Calculate Euclidean distance between the two laptops based on selected attributes
        double distance = 0.0;
        distance += pow(price - other.price, 2);
        distance += pow(ram - other.ram, 2);
        distance += pow(storage - other.storage, 2);
        distance += pow(battery - other.battery, 2);
        distance += pow(screen - other.screen, 2);
        distance += pow(weight - other.weight, 2);
        return sqrt(distance);
    }

    // Method to display similar laptops
    void displaySimilarLaptops(const vector<Laptop> &allLaptops) const
    {
        cout << "Do you want to see similar laptops to " << name << "? (yes/no): ";
        string answer;
        cin >> answer;

        if (answer == "yes")
        {
            cout << "Similar Laptops:" << endl;
            bool foundSimilar = false;
            for (const auto &other : allLaptops)
            {
                if (name != other.name)
                {
                    double score = calculateSimilarityScore(other);
                    cout << "- " << other.name << " (Similarity Score: " << score << ")" << endl;
                    foundSimilar = true;
                }
            }
            if (!foundSimilar)
            {
                cout << "No similar laptops found." << endl;
            }
        }
        else if (answer == "no")
        {
            cout << "Okay, not showing similar laptops." << endl;
        }
        else
        {
            cout << "Invalid input. Redirecting to the main menu." << endl;
        }
    }
};

struct FeatureGroup
{
    string name;
    vector<string> features;
};

map<string, double> userWeights;

int calculateWeightedScore(const Laptop &laptop)
{
    double score = 0;
    for (auto it = userWeights.begin(); it != userWeights.end(); ++it)
    {
        const string &feature = it->first;
        double weight = it->second;
        if (feature == "processor")
        {
            double speed = stod(laptop.processor.substr(laptop.processor.find_last_of(" ") + 1));
            score += speed * weight;
        }
        else if (feature == "graphicsCard")
        {
            score += (laptop.graphicsCard.find("Nvidia") != string::npos ? 10 : 5) * weight;
        }
        else if (feature == "RAM")
        {
            score += laptop.ram * weight;
        }
        else if (feature == "weight")
        {
            score += laptop.weight * weight;
        }
        else if (feature == "screen")
        {
            score += laptop.screen * weight;
        }
        else if (feature == "battery")
        {
            score += laptop.battery * weight;
        }
        else if (feature == "powerUser")
        {
            score += (laptop.powerUser ? 10 : 0) * weight; 
        }
        else if (feature == "generalUse")
        {
            score += (laptop.generalUse ? 10 : 0) * weight; 
        }
        else if (feature == "lightTasks")
        {
            score += (laptop.lightTasks ? 10 : 0) * weight; 
        }
    }
    return static_cast<int>(score);
}

bool compareWithWeights(const Laptop &l1, const Laptop &l2)
{
    return calculateWeightedScore(l1) > calculateWeightedScore(l2);
}

vector<string> selectedCriteria;

bool compareWithMultipleCriteria(const Laptop &l1, const Laptop &l2)
{
    for (const auto &criterion : selectedCriteria)
    {
        if (criterion == "price")
        {
            if (l1.price != l2.price)
            {
                return l1.price < l2.price;
            }
        }
        else if (criterion == "processor")
        {
            if (l1.processor != l2.processor)
            {
                return l1.processor < l2.processor;
            }
        }
        else if (criterion == "ram")
        {
            if (l1.ram != l2.ram)
            {
                return l1.ram > l2.ram;
            }
        }
        else if (criterion == "storage")
        {
            if (l1.storage != l2.storage)
            {
                return l1.storage > l2.storage;
            }
        }
        else if (criterion == "battery")
        {
            if (l1.battery != l2.battery)
            {
                return l1.battery > l2.battery;
            }
        }
        else if (criterion == "screen")
        {
            if (l1.screen != l2.screen)
            {
                return l1.screen > l2.screen;
            }
        }
        else if (criterion == "weight")
        {
            if (l1.weight != l2.weight)
            {
                return l1.weight < l2.weight;
            }
        }
        else if (criterion == "graphicsCard")
        {
            if (l1.graphicsCard != l2.graphicsCard)
            {
                return l1.graphicsCard.find("Nvidia") != string::npos;
            }
        }
        else if (criterion == "powerUser")
        {
            if (l1.powerUser != l2.powerUser)
            {
                return l1.powerUser;
            }
        }
        else if (criterion == "generalUse")
        {
            if (l1.generalUse != l2.generalUse)
            {
                return l1.generalUse;
            }
        }
        else if (criterion == "lightTasks")
        {
            if (l1.lightTasks != l2.lightTasks)
            {
                return l1.lightTasks;
            }
        }
    }
    return false;
}

void performScaling(vector<Laptop> &laptops)
{
    double scalingFactor;
    bool validScalingFactor = false;
    cout << "Enter scaling factor (1 for no change, less than 1 for reduction, greater than 1 for increase): ";
    cin >> scalingFactor;

    // Validate the input to ensure it's a positive number
    while (cin.fail() || scalingFactor <= 0)
    {
        cout << "Invalid scaling factor. Please enter a positive number: ";
        cin.clear();                                         // Clear the fail bit
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard input buffer
        cin >> scalingFactor;
    }

    // Scale the prices of laptops
    for (auto &laptop : laptops)
    {
        laptop.scalePrice(scalingFactor);
    }

    // Provide feedback to the user
    if (scalingFactor == 1)
    {
        cout << "Prices remain unchanged." << endl;
    }
    else if (scalingFactor < 1)
    {
        cout << "Prices reduced by " << ((1 - scalingFactor) * 100) << "%." << endl;
    }
    else
    {
        cout << "Prices increased by " << ((scalingFactor - 1) * 100) << "%." << endl;
    }
}

vector<Laptop> performSearching(const vector<Laptop> &laptops)
{
    // Perform searching based on user preference
    string keyword;
    cout << "Enter keyword to search: ";
    cin.ignore();
    getline(cin, keyword);

    vector<Laptop> searchResults;
    for (const auto &laptop : laptops)
    {
        if (laptop.name.find(keyword) != string::npos || laptop.brand.find(keyword) != string::npos ||
            laptop.processor.find(keyword) != string::npos || laptop.graphicsCard.find(keyword) != string::npos)
        {
            searchResults.push_back(laptop);
        }
    }

    if (searchResults.empty())
    {
        cout << "No laptops found matching the search criteria." << endl;
    }
    else
    {
        cout << "Search Results:" << endl;
        for (const auto &result : searchResults)
        {
            result.display();
            cout << endl;
        }
    }

    return searchResults; // Return the vector of search results
}

int main()
{
    cout << "\n                                                      --------------------------------------------------------------------------------" << endl;
    cout << "                                                                                    WELCOME TO SAVVY" << endl;
    cout << "\n                                    -----------------------------------------------------------------------------------" << endl;
    // Create a vector of Laptop objects and initialize them with some sample data
    vector<Laptop> laptops = {
        {"MacBook Pro", "Apple", 2399, "Intel Core i9 2.3 GHz", "Intel", 8, 16, 512, 100, 16, 2, "AMD Radeon Pro 5600M", true, false, false},
        {"Surface Laptop 4", "Microsoft", 1299, "AMD Ryzen 5 4680U", "AMD", 6, 8, 256, 47, 15, 1.3, "AMD Radeon Graphics", false, true, false},
        {"HP Spectre x360", "HP", 1599, "Intel Core i7 2.8 GHz", "Intel", 8, 16, 512, 72, 13.3, 1.27, "Intel Iris Xe Graphics", true, false, false},
        {"Swift 3", "Acer", 899, "AMD Ryzen 7 5700U", "AMD", 8, 16, 512, 56, 14, 1.2, "AMD Radeon Graphics", false, true, false},
        {"ZenBook 14", "Asus", 1099, "Intel Core i5 2.4 GHz", "Intel", 4, 8, 256, 63, 14, 1.19, "Intel Iris Xe Graphics", false, true, false},
        {"Envy x360", "HP", 949, "AMD Ryzen 5 4500U", "AMD", 6, 8, 256, 51, 15.6, 1.75, "AMD Radeon Graphics", false, true, false},
        {"XPS 15", "Dell", 1899, "Intel Core i7 2.6 GHz", "Intel", 6, 16, 512, 97, 15.6, 2, "Nvidia GTX 1650", true, false, false},
        {"ThinkPad X1 Carbon", "Lenovo", 1499, "Intel Core i5 1.6 GHz", "Intel", 4, 8, 256, 51, 14, 1.1, "Intel UHD Graphics", false, true, false},
        {"Aspire 5", "Acer", 549, "Intel Core i3 1.2 GHz", "Intel", 2, 4, 128, 48, 15.6, 1.9, "Intel UHD Graphics 620", false, false, true},
        {"ROG Zephyrus G14", "Asus", 1449, "AMD Ryzen 9 3.0 GHz", "AMD", 8, 16, 512, 76, 14, 1.6, "Nvidia RTX 3060", true, false, false},
        {"Nitro V", "Acer", 800, "Intel Core i5 3.4 GHz", "Intel", 8, 16, 512, 57, 15.6, 2, "Nvidia RTX 4050", true, false, false},
        {"HP Spectre x360 14-eu0556TU (9T8K6PA)", "HP", 168990, "Intel Core Ultra 7 4.8 GHz", "Intel", 4, 32, 1024, 1440, 14, 1.44, "Intel Iris Xe Graphics", true, false, false},
        {"MSI Bravo 15 B5DD-410IN", "MSI", 990, "AMD Hexa Core Ryzen 5 3.3 GHz", "AMD", 8, 8, 512, 1920, 15.6, 2.35, "N/A", false, true, false},
        {"HP 14s-dy2507TU (6N024PA)", "HP", 199, "Intel Core i3 11th Gen 4.2 GHz", "Intel", 2, 8, 256, 1920, 14, 1.41, "N/A", false, true, false},
        {"Infinix INBook X1 Neo XL22", "Infinix", 990, "Intel Celeron Quad Core 1.1 GHz", "Intel", 4, 8, 256, 1920, 14, 1.24, "N/A", false, true, false},
        {"Asus VivoBook 15 X515JA-BQ322WS", "Asus", 990, "Intel Core i3 10th Gen 1.2 GHz", "Intel", 2, 8, 512, 1920, 15.6, 1.8, "N/A", false, true, false},
        {"Lenovo Ideapad 1 11IGL05 (81VT009UIN)", "Lenovo", 23250, "Intel Celeron Dual Core 1.1 GHz", "Intel", 2, 4, 256, 1366, 11.6, 1.2, "N/A", false, true, false},
        {"HP 15s-eq2143au (50M62PA)", "HP", 32191, "AMD Quad Core Ryzen 3 2.6 GHz", "AMD", 8, 8, 512, 1920, 15.6, 1.69, "N/A", false, true, false},
        {"HP Pavilion 14-dv1001TU (50N47PA)", "HP", 999, "Intel Core i5 11th Gen", "Intel", 0, 16, 512, 1920, 14, 1.41, "N/A", false, true, false},
        {"Asus VivoBook 15 X515JA-EJ362WS", "Asus", 990, "Intel Core i3 10th Gen 1.2 GHz", "Intel", 2, 8, 512, 1920, 15.6, 1.8, "N/A", false, true, false},
        {"HP Pavilion 15-ec2004AX (3E3R5PA)", "HP", 990, "AMD Hexa Core Ryzen 5 3.3 GHz", "AMD", 6, 8, 512, 1920, 15.6, 1.98, "N/A", false, false, true},
        {"Xiaomi RedmiBook 15 Pro", "Xiaomi", 399, "Intel Core i5 11th Gen 3.1 GHz", "Intel", 4, 8, 512, 1920, 15.6, 1.8, "N/A", false, false, false},
        {"HP 15s-eq0500AU (440L6PA)", "HP", 410, "AMD Quad Core Ryzen 5 2.1 GHz", "AMD", 4, 8, 512, 1920, 15.6, 1.69, "N/A", false, false, false},
        {"Apple MacBook Air M1 MGN93HN/A Ultrabook", "Apple", 99900, "Apple M1 2.9 GHz", "Apple", 8, 8, 256, 2560, 13.3, 1.29, "N/A", false, false, false},
        {"Asus X543MA-GQ1015T", "Asus", 790, "Intel Celeron Dual Core 1.1 GHz", "Intel", 2, 4, 1024, 1366, 15.6, 27.2, "N/A", false, false, false},
        {"Acer Aspire 7 A715-51G (NH.QGCSI.001)", "Acer", 699, "Intel Core i5 12th Gen 3.3 GHz", "Intel", 4, 8, 512, 1920, 15.6, 19.9, "N/A", false, true, true},
        {"Acer Swift X SFX16-51G (NX.AYKSI.001)", "Acer", 949, "Intel Core i5 11th Gen 2.5 GHz", "Intel", 4, 16, 512, 1920, 16.1, 18.9, "N/A", false, true, false},
        {"Apple MacBook Pro M1 Pro MK193HN/A Ultrabook", "Apple", 236, "Apple M1 Pro 2.3 GHz", "Apple", 8, 16, 1024, 3456, 16.2, 16.8, "N/A", false, false, false},
        {"Asus TUF Gaming FX506HCB-HN225T", "Asus", 79939, "Intel Core i7 11th Gen 4.7 GHz", "Intel", 6, 16, 1024, 1920, 15.6, 22, "N/A", false, false, true},
        {"HP Spectre x360 14-eu0556TU (9T8K6PA)", "HP", 168990, "Intel Core Ultra 7 4.8 GHz", "Intel", 8, 32, 1024, 2880, 14, 1.44, "N/A", true, false, false},
        {"Dell Vostro 14 3401 (D552149WIN9BE)", "Dell", 39890, "Intel Core i3 10th Gen 1.2 GHz", "Intel", 2, 8, 1024, 1920, 14, 20, "N/A", false, false, true},
        {"Apple MacBook Air M1 MGN93HN/A Ultrabook", "Apple", 99900, "Apple M1 2.9 GHz", "Apple", 8, 8, 256, 2560, 13.3, 1.29, "N/A", false, false, false},
        {"Asus X543MA-GQ1015T", "Asus", 21790, "Intel Celeron Dual Core 1.1 GHz", "Intel", 2, 4, 1024, 1366, 15.6, 27.2, "N/A", false, false, false},
        {"Acer Aspire 7 A715-51G (NH.QGCSI.001)", "Acer", 69990, "Intel Core i5 12th Gen 3.3 GHz", "Intel", 4, 8, 512, 1920, 15.6, 19.9, "N/A", false, true, true},
        {"Acer Swift X SFX16-51G (NX.AYKSI.001)", "Acer", 94999, "Intel Core i5 11th Gen 2.5 GHz", "Intel", 4, 16, 512, 1920, 16.1, 18.9, "N/A", false, true, false},
        {"MSI Modern 14 B5M-242IN", "MSI", 34307, "AMD Hexa Core Ryzen 5 2.1 GHz", "AMD", 6, 8, 512, 1920, 14, 18.1, "N/A", false, true, false},
        {"Apple MacBook Pro M1 Pro MK193HN/A Ultrabook", "Apple", 236990, "Apple M1 Pro 2.3 GHz", "Apple", 8, 16, 1024, 3456, 16.2, 16.8, "N/A", false, false, false},
        {"Asus TUF Gaming FX506HCB-HN225T", "Asus", 79939, "Intel Core i7 11th Gen 4.7 GHz", "Intel", 6, 16, 1024, 1920, 15.6, 22, "N/A", false, false, true},
        {"HP Pavilion 15-ec2004AX (3E3R5PA)", "HP", 56990, "AMD Hexa Core Ryzen 5 3.3 GHz", "AMD", 6, 8, 512, 1920, 15.6, 1.98, "N/A", false, false, true},
        {"Xiaomi RedmiBook 15 Pro", "Xiaomi", 39990, "Intel Core i5 11th Gen 3.1 GHz", "Intel", 4, 8, 512, 1920, 15.6, 1.8, "N/A", false, false, false},
        {"HP 15s-eq0500AU (440L6PA)", "HP", 41000, "AMD Quad Core Ryzen 5 2.1 GHz", "AMD", 4, 8, 512, 1920, 15.6, 1.69, "N/A", false, false, false},
        {"Apple MacBook Air M1 MGN63HN/A Ultrabook", "Apple", 72490, "Apple M1 2.9 GHz", "Apple", 8, 8, 256, 2560, 13.3, 1.29, "N/A", false, false, false},
        };

    char choice;
    bool searched = false; // To track if search operation has been performed
    do
    {
        searched = false; // Reset the flag at the beginning of each iteration

        // Ask the user if they want to perform scaling, searching, or exit the program
        cout << "Enter your choice:" << endl;
        cout << "|| s. Perform scaling" << endl;
        cout << "|| d. Perform searching" << endl;
        cout << "|| n. Exit the program" << endl;
        cout << "|| Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 's':
            performScaling(laptops);
            break;
        case 'd':
            laptops = performSearching(laptops);
            searched = true;
            break;
        case 'n':
            break;
        default:
            cout << "Invalid choice. Please enter 's' for scaling, 'd' for searching, or 'n' to exit." << endl;
            break;
        }

        if (choice == 'n')
            break;

        // Clear the vectors and map for the next iteration
        userWeights.clear();
        selectedCriteria.clear();

        // If search operation has been performed, skip selection of criteria
        if (!searched)
        {
            // Feature groups
            vector<FeatureGroup> groups = {
                {"Performance", {"processor", "graphicsCard", "ram"}},
                {"Portability", {"weight"}}};

            // Ask the user to rate the importance of each feature
            cout << "Rate the importance of each feature on a scale of 1-5:" << endl;
            for (const auto &group : groups)
            {
                cout << group.name << ":" << endl;
                for (const auto &feature : group.features)
                {
                    double weight;
                    cout << "  " << feature << ": ";
                    cin >> weight;
                    if (cin.fail())
                    {
                        // Handle invalid input
                        cin.clear();                                         // clear the fail bit
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard input buffer
                        weight = 0;                                          // default weight
                    }
                    userWeights[feature] = weight;
                }
            }

            // Ask the user to select criteria
            cout << "Select criteria (multiple choices allowed):" << endl;
            for (const auto &group : groups)
            {
                cout << group.name << ":" << endl;
                for (const auto &feature : group.features)
                {
                    string choice;
                    cout << "  Include " << feature << "? (yes/no): ";
                    cin >> choice;
                    if (choice == "yes")
                    {
                        selectedCriteria.push_back(feature);
                    }
                }
            }
        }

        // Ask the user for the maximum number of laptops to display if search operation has not been performed
        if (!searched)
        {
            int maxLaptops;
            cout << "\nEnter the maximum number of laptops to display: ";
            cin >> maxLaptops;

            // Sorting laptops based on user-selected criteria
            sort(laptops.begin(), laptops.end(), compareWithMultipleCriteria);

            // Display sorted laptops (limited to maxLaptops)
            cout << "\nTop " << maxLaptops << " laptops based on selected criteria:" << endl;
            int count = 0;
            for (const auto &laptop : laptops)
            {
                if (count >= maxLaptops)
                {
                    break;
                }
                laptop.display();
                cout << endl;
                count++;
            }

            // Ask the user if they want to see similar laptops
            cout << "\nWould you like to see similar laptops to any of the displayed ones? (yes/no): ";
            string answer;
            cin >> answer;
            if (answer == "yes")
            {
                // Select a laptop
                int laptopIndex;
                cout << "Enter the index of the laptop you want to find similar ones to: ";
                cin >> laptopIndex;
                if (laptopIndex >= 0 && laptopIndex < laptops.size())
                {
                    laptops[laptopIndex].displaySimilarLaptops(laptops);
                }
                else
                {
                    cout << "Invalid laptop index." << endl;
                }
            }
        }

    } while (choice != 'n');

    cout << "\n                                                      --------------------------------------------------------------------------------" << endl;
    cout << "                                                                                    Thank you for using Savvy. " << endl;
    cout << "\n                                    -----------------------------------------------------------------------------------" << endl;

    return 0;
}

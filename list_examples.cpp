#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include <iomanip>

// Task class to represent a task in a task manager
class Task {
private:
    int id;
    std::string description;
    int priority;  // 1-5, where 5 is highest priority

public:
    Task(int taskId, std::string desc, int prio) 
        : id(taskId), description(desc), priority(prio) {}
    
    // Getters
    int getId() const { return id; }
    std::string getDescription() const { return description; }
    int getPriority() const { return priority; }
    
    // Setters
    void setPriority(int prio) { priority = prio; }
    
    // Display task information
    void display() const {
        std::cout << std::left << std::setw(5) << id 
                  << std::setw(40) << description 
                  << "Priority: " << priority << std::endl;
    }
    
    // Comparison operators for sorting
    bool operator<(const Task& other) const {
        return priority > other.priority;  // Higher priority first
    }
};

// TaskManager class to demonstrate list operations
class TaskManager {
private:
    std::list<Task> tasks;
    int nextId;

public:
    TaskManager() : nextId(1) {}
    
    // Add a new task to the end of the list
    void addTask(const std::string& description, int priority) {
        tasks.push_back(Task(nextId++, description, priority));
        std::cout << "Task added successfully." << std::endl;
    }
    
    // Add a high priority task to the beginning of the list
    void addUrgentTask(const std::string& description) {
        tasks.push_front(Task(nextId++, description, 5));
        std::cout << "Urgent task added at the beginning of the list." << std::endl;
    }
    
    // Remove a task by ID
    bool removeTask(int id) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [id](const Task& task) { return task.getId() == id; });
        
        if (it != tasks.end()) {
            tasks.erase(it);
            std::cout << "Task #" << id << " removed successfully." << std::endl;
            return true;
        }
        
        std::cout << "Task #" << id << " not found." << std::endl;
        return false;
    }
    
    // Move a task to the front of the list (mark as urgent)
    bool markAsUrgent(int id) {
        auto it = std::find_if(tasks.begin(), tasks.end(),
            [id](const Task& task) { return task.getId() == id; });
        
        if (it != tasks.end()) {
            // Create a copy of the task with highest priority
            Task urgentTask = *it;
            urgentTask.setPriority(5);
            
            // Remove the original task
            tasks.erase(it);
            
            // Add the urgent task at the front
            tasks.push_front(urgentTask);
            
            std::cout << "Task #" << id << " marked as urgent." << std::endl;
            return true;
        }
        
        std::cout << "Task #" << id << " not found." << std::endl;
        return false;
    }
    
    // Sort tasks by priority
    void sortByPriority() {
        tasks.sort();  // Uses the < operator defined in Task class
        std::cout << "Tasks sorted by priority." << std::endl;
    }
    
    // Merge with another task list
    void mergeLists(TaskManager& other) {
        // Sort both lists first
        tasks.sort();
        other.tasks.sort();
        
        // Merge the other list into this one
        tasks.merge(other.tasks);
        std::cout << "Task lists merged successfully." << std::endl;
    }
    
    // Reverse the order of tasks
    void reverseOrder() {
        tasks.reverse();
        std::cout << "Task order reversed." << std::endl;
    }
    
    // Display all tasks
    void displayTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks available." << std::endl;
            return;
        }
        
        std::cout << "\n===== Task List =====" << std::endl;
        std::cout << std::left << std::setw(5) << "ID" 
                  << std::setw(40) << "Description" 
                  << "Priority" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        
        for (const auto& task : tasks) {
            task.display();
        }
        
        std::cout << "\nTotal tasks: " << tasks.size() << std::endl;
    }
    
    // Demonstrate splicing operations
    void demonstrateSplice(TaskManager& other) {
        if (tasks.empty() || other.tasks.empty()) {
            std::cout << "Both task lists must have tasks for splicing." << std::endl;
            return;
        }
        
        // Splice entire other list at the end of this list
        std::cout << "Splicing entire second list to the end of first list..." << std::endl;
        tasks.splice(tasks.end(), other.tasks);
        
        std::cout << "After splicing, second list size: " << other.tasks.size() << std::endl;
    }
};

// Main function to demonstrate list operations
int main() {
    TaskManager personalTasks;
    TaskManager workTasks;
    
    std::cout << "===== STL List Demonstration: Task Manager =====" << std::endl;
    
    // Add tasks to personal list
    personalTasks.addTask("Buy groceries", 3);
    personalTasks.addTask("Call mom", 2);
    personalTasks.addTask("Pay bills", 4);
    personalTasks.addUrgentTask("Fix leaking pipe");
    
    // Display personal tasks
    std::cout << "\nPersonal Tasks:" << std::endl;
    personalTasks.displayTasks();
    
    // Add tasks to work list
    workTasks.addTask("Prepare presentation", 4);
    workTasks.addTask("Reply to emails", 3);
    workTasks.addTask("Schedule meeting", 2);
    
    // Display work tasks
    std::cout << "\nWork Tasks:" << std::endl;
    workTasks.displayTasks();
    
    // Demonstrate list operations
    std::cout << "\n===== List Operations Demonstration =====" << std::endl;
    
    // 1. Remove a task
    std::cout << "\n1. Removing a task:" << std::endl;
    personalTasks.removeTask(2);
    personalTasks.displayTasks();
    
    // 2. Mark a task as urgent (move to front)
    std::cout << "\n2. Marking a task as urgent:" << std::endl;
    personalTasks.markAsUrgent(3);
    personalTasks.displayTasks();
    
    // 3. Sort tasks by priority
    std::cout << "\n3. Sorting tasks by priority:" << std::endl;
    workTasks.sortByPriority();
    workTasks.displayTasks();
    
    // 4. Reverse order
    std::cout << "\n4. Reversing task order:" << std::endl;
    workTasks.reverseOrder();
    workTasks.displayTasks();
    
    // 5. Demonstrate splicing
    std::cout << "\n5. Demonstrating splice operation:" << std::endl;
    std::cout << "Before splicing:" << std::endl;
    std::cout << "Personal tasks:" << std::endl;
    personalTasks.displayTasks();
    std::cout << "Work tasks:" << std::endl;
    workTasks.displayTasks();
    
    personalTasks.demonstrateSplice(workTasks);
    
    std::cout << "\nAfter splicing:" << std::endl;
    std::cout << "Personal tasks (now includes work tasks):" << std::endl;
    personalTasks.displayTasks();
    std::cout << "Work tasks (should be empty):" << std::endl;
    workTasks.displayTasks();
    
    // 6. Create a new list for demonstration
    TaskManager newTasks;
    newTasks.addTask("Research new project", 5);
    newTasks.addTask("Update software", 3);
    
    // 7. Merge lists
    std::cout << "\n6. Merging task lists:" << std::endl;
    std::cout << "Before merging:" << std::endl;
    std::cout << "Personal tasks:" << std::endl;
    personalTasks.displayTasks();
    std::cout << "New tasks:" << std::endl;
    newTasks.displayTasks();
    
    personalTasks.mergeLists(newTasks);
    
    std::cout << "\nAfter merging:" << std::endl;
    std::cout << "Personal tasks (now includes new tasks):" << std::endl;
    personalTasks.displayTasks();
    std::cout << "New tasks (should be empty after merge):" << std::endl;
    newTasks.displayTasks();
    
    std::cout << "\n===== End of STL List Demonstration =====" << std::endl;
    
    return 0;
}

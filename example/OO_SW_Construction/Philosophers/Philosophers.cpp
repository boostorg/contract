/**
 * @file
 * @author Copyright (C) 2009 Lorenzo Caminiti.
 *  Distributed under DBC++ Software License (see file LICENSE_1_0.txt).
 */

#include <dbc/separate.hpp>
#include <dbc/process.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Fork {
public:
    int seat;

    explicit Fork(): seat(-1) {}

    friend std::ostream& operator<<(std::ostream& s, const Fork& o)
        { return s << o.seat; }
};

class BasicPhilosopher {
public:
    int seat;
    
    explicit BasicPhilosopher(dbc::separate<Fork>::arg left,
            dbc::separate<Fork>::arg right):
            seat(-1), left_(left), right_(right), thinkingSeconds_(0) {
        srand(time(NULL));
        thinkingSeconds_ = rand() % 10;
    }
    
    unsigned int thinkingSeconds() const { return thinkingSeconds_; }
    
    friend std::ostream& operator<<(std::ostream& s, const BasicPhilosopher& o)
        { return s << o.seat; }
    
protected:
    void getup() {}

    void think() {
        std::cout << "Philosopher " << *this << " thinking for "
                << thinkingSeconds_ << " second(s)..." << std::endl;
        sleep(thinkingSeconds_);
    }

    dbc::separate<Fork> left_;
    dbc::separate<Fork> right_;
    unsigned int thinkingSeconds_;
};

class Philosopher: public BasicPhilosopher, public dbc::process,
        boost::noncopyable {
public:
    explicit Philosopher(dbc::separate<Fork>::arg left,
            dbc::separate<Fork>::arg right):
            BasicPhilosopher(left, right) {}

    virtual ~Philosopher()
        { std::cout << "Philosopher " << *this << " is done" << std::endl; }

private:
    void setup() { getup(); }

    void step() {
        think();
        eat(left_, right_);
    }

    void eat(dbc::separate<Fork>::arg left,
            dbc::separate<Fork>::arg right) {
        std::cout << "Philosopher " << *this << " has eatten using left fork "
                << left << " and right fork " << right << std::endl;
        over(true);
    }
};

class Butler {
public:
    Butler(const size_t& n): cutley_(), philosophers_() {
        for (size_t seat = 0; seat < n; seat++) {
            dbc::separate<Fork> fork;
            fork->*&Fork::seat = seat;
            cutley_.push_back(fork);
        }
        for (size_t seat = 0; seat < cutley_.size(); seat++) {
            dbc::separate<Fork>& left(cutley_.at(seat));
            dbc::separate<Fork>&
                    right(cutley_.at((seat + 1) % cutley_.size()));

            // Construct (separate<Philosopher> has same constrcutors as
            // Philosopher).
            std::clog << "Creating philosopher " << seat << std::endl;
            dbc::separate<Philosopher> phil(left, right);
            // Write member variable (async).
            std::clog << "Seating philosopher " << seat << std::endl;
            phil->*&Philosopher::seat = seat;
            // Copy (separte<Philosopher> is copyable even if Philosopher is 
            // not).
            philosophers_.push_back(phil);
        }
    }

    size_t count() const { return cutley_.size(); }

    void launch() {
        for (size_t i = 0; i < cutley_.size(); i++) {
            dbc::separate<Philosopher>& phil(philosophers_.at(i));

            // Call query-like member function (sync).
            unsigned int sec = (phil->*&Philosopher::thinkingSeconds)();
            // Read member variable (sync).
            size_t seat = phil->*&Philosopher::seat;
            std::cout << "Philosopher " << phil << " seated at " << seat
                    << " will think for about " << sec
                    << " seconds before eating" << std::endl;
            
            // Call command-like member function (async).
            (phil->*&Philosopher::live)();
        }
    }

private:
    std::vector<dbc::separate<Fork> > cutley_;
    std::vector<dbc::separate<Philosopher> > philosophers_;
};

int main() {
    Butler b(3);
    b.launch();
    return 0;
}


#include "index.c"

int main(int argc, char **argv)
{
    init();
    // loop();
    Map *m = newMap();
    m->proto->set(m, "toto", "titi");
    m->proto->set(m, "titi", "toto");
    m->proto->set(m, "tata", "tutu");
    m->proto->set(m, "tutu", "tata");
    m->proto->set(m, "totototo", "titititi");
    m->proto->set(m, "titititi", "totototo");
    m->proto->set(m, "tatatata", "tutututu");
    m->proto->set(m, "tutututu", "tatatata");
    m->proto->set(m, "foo", "bar");
    m->proto->set(m, "bar", "foo");
    m->proto->set(m, "trtr", "titi");
    m->proto->set(m, "tete", "titi");
    m->proto->set(m, "tztz", "titi");
    m->proto->set(m, "thth", "titi");
    m->proto->set(m, "tgtg", "titi");
    m->proto->set(m, "tjtj", "titi");
    m->proto->set(m, "tktk", "titi");
    m->proto->set(m, "tntt", "titi");
    m->proto->set(m, "thnt", "titi");
    m->proto->set(m, "tobbtto", "titi");
    puts(m->proto->set(m, "tntt", "toto"));
    puts(m->proto->get(m, "tntt"));
    return 0;
}
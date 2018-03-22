#ifndef SCHMOUTSE_CHARGEUR_H
#define SCHMOUTSE_CHARGEUR_H


class Chargeur
{
    public:
        static Chargeur& getInstance()
        {
            static Chargeur c;
            return c;
        };
        Chargeur(const Chargeur&) = delete;
        Chargeur& operator=(const Chargeur&) = delete;
    
    private:
        Chargeur() = default;
};


#endif //SCHMOUTSE_CHARGEUR_H

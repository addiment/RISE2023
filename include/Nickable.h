#ifndef TOOLKITENGINEV3_NICKABLE_H
#define TOOLKITENGINEV3_NICKABLE_H



class Nickable {
public:
    void setNickname(const char* nick);
    [[nodiscard]] const char* getNickname() const;
    [[nodiscard]] const char* getPrintNickname() const;
    explicit Nickable(const char* nick = nullptr);
protected:
    const char* nickname = nullptr;
};

#endif //TOOLKITENGINEV3_NICKABLE_H

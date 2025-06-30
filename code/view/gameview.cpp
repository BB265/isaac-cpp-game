#include"gameview.h"
gamewindow::gamewindow() :isaac_sprite(normal_texture),enemy_sprite(normal_texture), tears_sprite(normal_texture), backgroundSprite(normal_texture), heart_sprite(normal_texture) {
    window = sf::RenderWindow(sf::VideoMode({ WINDOW_WIDTH, WINDOW_HEIGHT }), "Isaac Game");
    backgroundSprite = createSprite("../code/assets/room.png", backgroundTexture);

    // ���ؽ�ɫ����;���
    
    isaac_sprite = createSprite("../code/assets/isaac.png", characterTexture);
    isaac_sprite.setPosition(sf::Vector2f( 400, 300 )); // ��ʼλ��

    // ��������ͼ������
    
    heart_sprite = createSprite("../code/assets/heart.png", heartTexture);
    heart_sprite.setScale(sf::Vector2f(0.05f, 0.05f )); // ��������ͼ���С
    heart_count = 3;

    
    enemy_sprite= createSprite("../code/assets/Champion_Red.png", enemy_Texture);

    
    tears_sprite= createSprite("../code/assets/tear.png", tears_Texture);
}
void gamewindow::draw_and_display() {
    window.clear();
    window.draw(backgroundSprite);
    window.draw(isaac_sprite);

    // ������
    for (int i = 0; i < heart_count; ++i) {
        heart_sprite.setPosition({ 10.f + i * 40.f, 10.f }); // ÿ���ĵļ��Ϊ 40
        window.draw(heart_sprite);
    }
    //���Ƶ��˺��ӵ�����δ���.
    window.display();
}
sf::Sprite gamewindow::createSprite(const std::string& filepath, sf::Texture& texture) {
    if (!texture.loadFromFile(filepath)) {
        throw std::runtime_error("Failed to load texture: " + filepath);
    }
    return sf::Sprite(texture);
}
void gamewindow::setposition(sf::Sprite& sprite, sf::Vector2f position) {
    sprite.setPosition(position);
}
void gamewindow::set_heartcount(int count) {
    heart_count = count;
}
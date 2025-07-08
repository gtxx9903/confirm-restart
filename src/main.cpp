#include <Geode/Geode.hpp>
using namespace geode::prelude;

bool confirmRestart = Mod::get()->getSavedValue<bool>("confirm-restart", false);
#include <Geode/modify/PauseLayer.hpp>
class $modify(MyPauseLayer, PauseLayer) {
    void customSetup() {
        PauseLayer::customSetup();

        auto checkbox = CCMenuItemToggler::createWithStandardSprites(this, menu_selector(MyPauseLayer::onHello), 1.0f);
		checkbox->toggle(confirmRestart);
		checkbox->setID("confirm-restart-checkbox"_spr);

		auto confirmRestartLabel = CCLabelBMFont::create("Confirm Restart", "bigFont.fnt");
		confirmRestartLabel->setID("confirm-restart-label"_spr);

		auto menu = this->getChildByID("bottom-button-menu");
		menu->setScale(0.6f);
		menu->addChild(checkbox);
		menu->addChild(confirmRestartLabel);
		menu->updateLayout();
    }
    void onHello(CCObject * sender) {
		confirmRestart = !confirmRestart;
		Mod::get()->setSavedValue("confirm-restart", confirmRestart);
    }
    void onRestart(CCObject * sender) {
        if (confirmRestart) {
            geode::createQuickPopup(
                "Restart",
                "Are you sure you want to <cr>restart</c>?",
                "Cancel", "Restart",
                [this, sender](auto, bool btn2) {
                    if (btn2) {
                        auto playLayer = GameManager::sharedState()->getPlayLayer();

                        playLayer->resetLevel();
                        this->onResume(nullptr);
					}
                }
            );
        }
        else {
			PauseLayer::onRestart(sender);
        }
    }
};

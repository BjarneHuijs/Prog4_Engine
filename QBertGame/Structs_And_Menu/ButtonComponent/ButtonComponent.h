#pragma once
#include <BaseComponent.h>

#include "../../Level/Levels/GameLevels.h"

class ButtonComponent : public Idiot_Engine::BaseComponent
{
public:
	ButtonComponent(const std::string& name, GameLevels* pLevel);

	void FixedUpdate(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void LateUpdate(const float deltaTime) override;
	void Render(const float nextFrame) const override;

	void SetNextButton(const std::string& name);
	void SetPreviousButton(const std::string& name);

	void MoveSelectionUp();
	void MoveSelectionDown();

	std::string GetSelectedButtonName() const;
	void Select();
	void DeSelect();

	std::shared_ptr<QBertComponent> GetUser() const;
	std::shared_ptr<QBertComponent> GetUser2() const;
private:
	std::string m_PreviousButtonName;
	std::string m_NextButtonName;
	bool m_bSelected;

	GameLevels* m_pLevel;
};


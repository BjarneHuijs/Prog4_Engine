#include "QBertGamePCH.h"
#include "ButtonComponent.h"

#include "GameObject.h"
#include "TextureComponent.h"
#include "../../Level/Levels/GameLevels.h"

ButtonComponent::ButtonComponent(const std::string& name, GameLevels* pLevels)
	: BaseComponent(name)
	, m_PreviousButtonName()
	, m_NextButtonName()
	, m_bSelected(false)
	, m_pLevel(pLevels)
{
}

void ButtonComponent::FixedUpdate(const float)
{
}

void ButtonComponent::Update(const float)
{
}

void ButtonComponent::LateUpdate(const float)
{
}

void ButtonComponent::Render(const float) const
{
}

void ButtonComponent::SetNextButton(const std::string& name)
{
	const std::weak_ptr<ButtonComponent> nextButton = m_pParent->GetComponentByName<ButtonComponent>(name);
	if(!nextButton.expired() && !name._Equal(m_NextButtonName))
	{
		m_NextButtonName = name;
		nextButton.lock()->SetPreviousButton(m_Name);
	}
}

void ButtonComponent::SetPreviousButton(const std::string& name)
{
	const std::weak_ptr<ButtonComponent> prevButton = m_pParent->GetComponentByName<ButtonComponent>(name);
	if (!prevButton.expired() && !name._Equal(m_PreviousButtonName))
	{
		m_PreviousButtonName = name;
		prevButton.lock()->SetNextButton(m_Name);
	}
}

void ButtonComponent::MoveSelectionUp()
{
	if(m_bSelected)
	{
		/*m_bSelected = false;
		m_pParent->GetComponentByName<Idiot_Engine::TextureComponent>(m_Name + "_Texture")->SetTexture(m_Name + ".png");*/
		DeSelect();
		const std::weak_ptr<ButtonComponent> prevButton = m_pParent->GetComponentByName<ButtonComponent>(m_PreviousButtonName);
		prevButton.lock()->Select();

	}
}

void ButtonComponent::MoveSelectionDown()
{
	if (m_bSelected) 
	{
		/*m_bSelected = false;
		m_pParent->GetComponentByName<Idiot_Engine::TextureComponent>(m_Name + "_Texture")->SetTexture(m_Name + ".png");*/
		DeSelect();
		const std::weak_ptr<ButtonComponent> nextButton = m_pParent->GetComponentByName<ButtonComponent>(m_NextButtonName);
		nextButton.lock()->Select();
	}
}

std::string ButtonComponent::GetSelectedButtonName() const
{
	if(m_bSelected)
	{
		return m_Name;
	}
	
	return m_pParent->GetComponentByName<ButtonComponent>(m_NextButtonName)->GetSelectedButtonName();
}

void ButtonComponent::Select()
{	
	m_bSelected = true;
	m_pParent->GetComponentByName<Idiot_Engine::TextureComponent>(m_Name + "_Texture")->SetTexture(m_Name + "_Selected.png");
}

void ButtonComponent::DeSelect()
{
	m_bSelected = false;
	m_pParent->GetComponentByName<Idiot_Engine::TextureComponent>(m_Name + "_Texture")->SetTexture(m_Name + ".png");
}

std::shared_ptr<QBertComponent> ButtonComponent::GetUser() const
{
	return m_pLevel->GetQBert();
}

std::shared_ptr<QBertComponent> ButtonComponent::GetUser2() const
{
	return m_pLevel->GetQBert2();
}

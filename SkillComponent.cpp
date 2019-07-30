#include "include/stdafx.h"
#include "include/SkillComponent.h"

SkillComponent::SkillComponent() {
  this->skills.push_back(Skill(SKILLS::HEALTH));
  this->skills.push_back(Skill(SKILLS::ATTACK));
  this->skills.push_back(Skill(SKILLS::ACCURACY));
  this->skills.push_back(Skill(SKILLS::ENDURANCE));
}


SkillComponent::~SkillComponent() {

}


const int SkillComponent::getSkill(const SKILLS skill) const {
  if(!skills.empty() && skill > 0 && skill < this->skills.size()) {
    return this->skills[skill].getLevel();
  } else {
    throw("ERROR::SKILLCOMPONENT::GETSKILL::SKILL DOES NOT EXIST" + skill);
  }
}


void SkillComponent::gainExp(const SKILLS skill, const int exp) {
  if(!skills.empty() && skill > 0 && skill < this->skills.size()) {
    return this->skills[skill].gainExp(exp);
  } else {
    throw("ERROR::SKILLCOMPONENT::GAINEXP::SKILL DOES NOT EXIST" + skill);
  }

}

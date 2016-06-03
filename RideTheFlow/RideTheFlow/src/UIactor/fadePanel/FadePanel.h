#pragma once

class FadePanel
{
private:
	FadePanel() = default;
	~FadePanel() = default;

public:
	static FadePanel &GetInstance(){
		static FadePanel f;
		return f;
	}

	void Initialize();
	void Update();
	void Draw() const;
	void FadeIn(float sec);
	void FadeOut(float sec);
	bool IsAction();
};
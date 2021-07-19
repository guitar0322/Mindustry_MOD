#include "stdafx.h"
#include "Transport.h"

void Transport::Init()
{
	_animator = gameObject->GetComponent<Animator>();
}

void Transport::Update()
{
}
/***************************************************************
* �����̾� ��Ʈ�� ���� �ɶ����� �ִϸ��̼� Ŭ���� ��ȯ ���ִ� �Լ�
* dir = ������ ���� ����
* outDir�� ���� ������ ��� �����Ѵ�
****************************************************************/
void Transport::LinkConveyor(PROPDIR dir)
{
	if (_outDir == dir)
		return;

	bool clock = true;
	if (dir - _outDir == -1 || dir - _outDir == 3)
	{
		clock = false;
	}
	if (_shape == O)
	{
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = I;
			_animator->SetClip("conveyor_I", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == false)
		{
			_shape = L;
			_animator->SetClip("conveyor_L", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == true)
		{
			_shape = L2;
			_animator->SetClip("conveyor_L2", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == I)
	{
		if (clock == false)
		{
			_shape = T3;
			_animator->SetClip("conveyor_T3", _firstConveyorAnimator->GetCurFrameX());
		}
		else if (clock == true)
		{
			_shape = T;
			_animator->SetClip("conveyor_T", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == L)
	{
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = T;
			_animator->SetClip("conveyor_T", _firstConveyorAnimator->GetCurFrameX());
		}
		else
		{
			_shape = T2;
			_animator->SetClip("conveyor_T2", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else if (_shape == L2)
	{
		if (Math::Abs(_outDir - dir) == 2)
		{
			_shape = T;
			_animator->SetClip("conveyor_T", _firstConveyorAnimator->GetCurFrameX());
		}
		else
		{
			_shape = T3;
			_animator->SetClip("conveyor_T3", _firstConveyorAnimator->GetCurFrameX());
		}
	}
	else
	{
		_shape = CROSS;
		_animator->SetClip("conveyor_cross", _firstConveyorAnimator->GetCurFrameX());
	}

	_animator->SetFrameTime(_firstConveyorAnimator->GetFrameTime());
	/***************************************************
	* ���� ����
	* ���� outDir �� dir�� ������ ����(Ŭ���� �ٲ��� ����)
	* Ŭ���� �ٲܶ� Ŭ�������Ӱ� �ð��� �����Ұ�
	* ���ῡ ���� �ٲ��� �Ұ�. angle, clip
	* O���� �ݴ�������� ������ I�� ��
	* O���� ������������ ������ L�� ��
	* T�� �ΰ���. 
	* T2�� ����� OUT�� ��
	* T1�� ���������� OUT�ΰ�
	* I���� ��������� ����ǵ� T1�� �ȴ�. ������ ���⿡ ���� �޶���
	* L���� OUT �� ������ �������� ������ T2�� �ݴ�����̸� T1
	* 
	* �ݴ������ dir ���̰� 2, ������ 1
	* T���� �����̵Ǹ� cross�� �ȴ�
	***************************************************/
}
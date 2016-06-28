#pragma once

//��C�C�̎��ʂ܂łɐi�ދ���
static const float WindBallLimitLength = 1500.0f;
//��C�C�̃X�s�[�h
static const float WindBallSpeed = 1000.0f;

//���������ʂ܂ł̎���(�b)
static const float TornadoLifeLimit = 20.0f;
//�����̃X�s�[�h
static const float TornadoSpeed = 600.0f;
//�����p�[�e�B�N���̏㏸�X�s�[�h�ő�ƍŏ�(�����_��)
static const float TornadoParticleRizeSpeedMax = 600.0f;
static const float TornadoParticleRizeSpeedMin = 500.0f;

//���ꂪ���ʂ܂ł̎���(�b)
static const float WindFlowLifeLimit = 20.0f;
//���ꂪ�^�b�N�����ꂽ�Ƃ��̔��ł��X�s�[�h
static const float WindFlowSpeed = 400.0f;

//�鑝�z���̉�
//��
static const int CastleAddSmokeNum = 12;
//�傫��
//�傫���̃x�[�X
static const float CastleAddSmokeSize = 0.03f;
//�x�[�X�ɉ�����ő�ƍŏ�(�����_��)
static const float CastleAddSmokeSizePlusMax = 0.01f;
static const float CastleAddSmokeSizePlusMin = -0.02f;
//������܂ł̎���(����s�D���_���[�W�H��������̉��ɂ��K�p)
static const float SmokeLifeLimit = 2.0f;


//����s�D���_���[�W�H��������̉�
//��
static const int DamageSmokeNum = 1;
//�傫��
static const float DamageSmokeSize = 0.03f;
static const float DamageSmokeSizePlusMax = 0.01f;
static const float DamageSmokeSizePlusMin = -0.02f;

// FUNC: public: void __thiscall idMsgChannel::Init(struct netadr_t,int)
void __thiscall idMsgChannel::Init(idMsgChannel *this, netadr_t adr, int id)
{
  this->remoteAddress = adr;
  this->id = id;
  this->maxRate = 50000;
  this->compressor = idCompressor::AllocRunLength_ZeroBased();
  this->lastSendTime = 0;
  this->lastDataBytes = 0;
  this->outgoingRateTime = 0;
  this->outgoingRateBytes = 0;
  this->incomingRateTime = 0;
  this->incomingRateBytes = 0;
  this->incomingReceivedPackets = 0.0;
  this->incomingDroppedPackets = 0.0;
  this->incomingPacketLossTime = 0;
  this->outgoingCompression = 0.0;
  this->incomingCompression = 0.0;
  this->outgoingSequence = 1;
  this->incomingSequence = 0;
  this->unsentFragments = 0;
  this->unsentFragmentStart = 0;
  this->fragmentSequence = 0;
  this->fragmentLength = 0;
  idMsgQueue::Init(&this->reliableSend, 1);
  idMsgQueue::Init(&this->reliableReceive, 0);
}

// FUNC: public: void __thiscall idMsgChannel::Shutdown(void)
void __thiscall idMsgChannel::Shutdown(idMsgChannel *this)
{
  idCompressor *compressor; // ecx

  compressor = this->compressor;
  if ( compressor )
    ((void (__thiscall *)(idCompressor *, int))compressor->~idCompressor)(compressor, 1);
  this->compressor = 0;
}

// FUNC: public: void __thiscall idMsgChannel::ResetRate(void)
void __thiscall idMsgChannel::ResetRate(idMsgChannel *this)
{
  this->lastSendTime = 0;
  this->lastDataBytes = 0;
  this->outgoingRateTime = 0;
  this->outgoingRateBytes = 0;
  this->incomingRateTime = 0;
  this->incomingRateBytes = 0;
}

// FUNC: public: bool __thiscall idMsgChannel::ReadyToSend(int)const
bool __thiscall idMsgChannel::ReadyToSend(idMsgChannel *this, int time)
{
  int maxRate; // eax
  int v3; // edx
  unsigned int v5; // edx

  maxRate = this->maxRate;
  if ( !maxRate )
    return 1;
  v3 = time - this->lastSendTime;
  if ( v3 > 1000 )
    return 1;
  v5 = (int)((unsigned __int64)(v3 * maxRate * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6;
  return (int)(this->lastDataBytes - (v5 + (v5 >> 31))) <= 0;
}

// FUNC: public: void __thiscall idMsgChannel::ClearReliableMessages(void)
void __thiscall idMsgChannel::ClearReliableMessages(idMsgChannel *this)
{
  idMsgQueue::Init(&this->reliableSend, 1);
  idMsgQueue::Init(&this->reliableReceive, 0);
}

// FUNC: private: void __thiscall idMsgChannel::UpdateOutgoingRate(int,int)
void __thiscall idMsgChannel::UpdateOutgoingRate(idMsgChannel *this, int time, int size)
{
  int v3; // eax
  int v4; // eax
  bool v5; // sf
  int v6; // eax

  v3 = time - this->lastSendTime;
  if ( v3 > 1000 || (v4 = v3 * this->maxRate / -1000, v5 = v4 + this->lastDataBytes < 0, this->lastDataBytes += v4, v5) )
    this->lastDataBytes = 0;
  this->lastDataBytes += size;
  v6 = time - this->outgoingRateTime;
  this->lastSendTime = time;
  if ( v6 > 1000 )
  {
    v5 = (int)(this->outgoingRateBytes
             - (((int)((unsigned __int64)(this->outgoingRateBytes
                                        * (v6 - 1000)
                                        * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
              + ((unsigned int)((unsigned __int64)(this->outgoingRateBytes
                                                 * (v6 - 1000)
                                                 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31))) < 0;
    this->outgoingRateBytes -= ((int)((unsigned __int64)(this->outgoingRateBytes
                                                       * (v6 - 1000)
                                                       * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
                             + ((unsigned int)((unsigned __int64)(this->outgoingRateBytes
                                                                * (v6 - 1000)
                                                                * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31);
    if ( v5 )
      this->outgoingRateBytes = 0;
  }
  this->outgoingRateBytes += size;
  this->outgoingRateTime = time - 1000;
}

// FUNC: private: void __thiscall idMsgChannel::UpdateIncomingRate(int,int)
void __thiscall idMsgChannel::UpdateIncomingRate(idMsgChannel *this, int time, int size)
{
  int v3; // eax
  bool v4; // sf

  v3 = time - this->incomingRateTime;
  if ( v3 > 1000 )
  {
    v4 = (int)(this->incomingRateBytes
             - (((int)((unsigned __int64)(this->incomingRateBytes
                                        * (v3 - 1000)
                                        * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
              + ((unsigned int)((unsigned __int64)(this->incomingRateBytes
                                                 * (v3 - 1000)
                                                 * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31))) < 0;
    this->incomingRateBytes -= ((int)((unsigned __int64)(this->incomingRateBytes
                                                       * (v3 - 1000)
                                                       * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 6)
                             + ((unsigned int)((unsigned __int64)(this->incomingRateBytes
                                                                * (v3 - 1000)
                                                                * (__int64)(int)&sessLocal.loggedUsercmds[29315].cmd.rightmove) >> 32) >> 31);
    if ( v4 )
      this->incomingRateBytes = 0;
  }
  this->incomingRateBytes += size;
  this->incomingRateTime = time - 1000;
}

// FUNC: private: void __thiscall idMsgChannel::UpdatePacketLoss(int,int,int)
void __thiscall idMsgChannel::UpdatePacketLoss(idMsgChannel *this, int time, int numReceived, int numDropped)
{
  int v4; // eax
  double v5; // st7
  double v6; // st6
  double v7; // st7

  v4 = time - this->incomingPacketLossTime;
  if ( v4 > 5000 )
  {
    v5 = (double)(v4 - 5000) * 0.00019999999;
    v6 = this->incomingReceivedPackets - v5 * this->incomingReceivedPackets;
    this->incomingReceivedPackets = v6;
    if ( v6 < 0.0 )
      this->incomingReceivedPackets = 0.0;
    v7 = this->incomingDroppedPackets - v5 * this->incomingDroppedPackets;
    this->incomingDroppedPackets = v7;
    if ( v7 < 0.0 )
      this->incomingDroppedPackets = 0.0;
  }
  this->incomingPacketLossTime = time - 5000;
  this->incomingReceivedPackets = (double)numReceived + this->incomingReceivedPackets;
  this->incomingDroppedPackets = (double)numDropped + this->incomingDroppedPackets;
}

// FUNC: public: float __thiscall idMsgChannel::GetIncomingPacketLoss(void)const
double __thiscall idMsgChannel::GetIncomingPacketLoss(idMsgChannel *this)
{
  if ( this->incomingReceivedPackets == 0.0 && this->incomingDroppedPackets == 0.0 )
    return 0.0;
  else
    return this->incomingDroppedPackets * 100.0 / (this->incomingDroppedPackets + this->incomingReceivedPackets);
}

// FUNC: public: void __thiscall idMsgChannel::Save(class idFile *)const
void __thiscall idMsgChannel::Save(idMsgChannel *this, idFile *file)
{
  file->WriteInt(file, this->incomingSequence);
  file->WriteInt(file, this->fragmentSequence);
  file->WriteInt(file, this->fragmentLength);
  file->Write(file, this->fragmentBuffer, this->fragmentLength);
  idMsgQueue::Save(&this->reliableReceive, file);
}

// FUNC: public: void __thiscall idMsgChannel::Restore(class idFile *)
void __thiscall idMsgChannel::Restore(idMsgChannel *this, idFile *file)
{
  file->ReadInt(file, &this->incomingSequence);
  file->ReadInt(file, &this->fragmentSequence);
  file->ReadInt(file, &this->fragmentLength);
  file->Read(file, this->fragmentBuffer, this->fragmentLength);
  idMsgQueue::Restore(&this->reliableReceive, file);
}

// FUNC: public: __thiscall idMsgChannel::idMsgChannel(void)
void __thiscall idMsgChannel::idMsgChannel(idMsgChannel *this)
{
  idBitMsg::idBitMsg(&this->unsentMsg);
  idMsgQueue::idMsgQueue(&this->reliableSend);
  idMsgQueue::idMsgQueue(&this->reliableReceive);
  this->id = -1;
}

// FUNC: private: void __thiscall idMsgChannel::WriteMessageData(class idBitMsg &,class idBitMsg const &)
void __thiscall idMsgChannel::WriteMessageData(idMsgChannel *this, idBitMsg *out, const idBitMsg *msg)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  void *v4; // esp
  int last; // eax
  int curSize; // ebx
  int v8; // eax
  idCompressor *compressor; // ecx
  idCompressor_vtbl *v10; // edx
  idBitMsg v11; // [esp+Ch] [ebp-405Ch] BYREF
  idFile_BitMsg v12; // [esp+30h] [ebp-4038h] BYREF
  char v13[16384]; // [esp+5Ch] [ebp-400Ch] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v14; // [esp+405Ch] [ebp-Ch]
  void *v15; // [esp+4060h] [ebp-8h]
  int v16; // [esp+4064h] [ebp-4h]

  v16 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v15 = &_ehhandler__WriteMessageData_idMsgChannel__AAEXAAVidBitMsg__ABV2__Z;
  v14 = ExceptionList;
  v4 = alloca(16464);
  idBitMsg::idBitMsg(&v11);
  v11.writeData = (unsigned __int8 *)v13;
  last = this->reliableReceive.last;
  v11.readData = (const unsigned __int8 *)v13;
  v11.maxSize = 0x4000;
  v11.numValueOverflows = 0;
  idBitMsg::WriteBits(&v11, last, 32);
  idMsgQueue::CopyToBuffer(&this->reliableSend, &v11.writeData[v11.curSize]);
  curSize = v11.curSize;
  v8 = curSize + idMsgQueue::GetTotalSize(&this->reliableSend);
  v11.curSize = v11.maxSize;
  if ( v8 <= v11.maxSize )
    v11.curSize = v8;
  idBitMsg::WriteBits(&v11, 0, -16);
  idBitMsg::WriteData(&v11, msg->readData, msg->curSize);
  idBitMsg::WriteBits(out, v11.curSize, -16);
  idFile_BitMsg::idFile_BitMsg(&v12, out);
  compressor = this->compressor;
  v10 = compressor->__vftable;
  v16 = 0;
  v10->Init(compressor, &v12, 1, 3);
  this->compressor->Write(this->compressor, v11.writeData, v11.curSize);
  this->compressor->FinishCompress(this->compressor);
  this->outgoingCompression = this->compressor->GetCompressionRatio(this->compressor);
  v16 = -1;
  idFile_BitMsg::~idFile_BitMsg(&v12);
}

// FUNC: private: bool __thiscall idMsgChannel::ReadMessageData(class idBitMsg &,class idBitMsg const &)
char __thiscall idMsgChannel::ReadMessageData(idMsgChannel *this, idBitMsg *out, idBitMsg *msg)
{
  struct _EXCEPTION_REGISTRATION_RECORD *ExceptionList; // eax
  const idBitMsg *v4; // ebx
  __int16 Bits; // ax
  int maxSize; // ecx
  idCompressor *compressor; // ecx
  idCompressor_vtbl *v9; // eax
  int v10; // ebx
  int v11; // eax
  bool v12; // cc
  int v14; // esi
  const char *v15; // eax
  idFile_BitMsg file; // [esp+14h] [ebp-38h] BYREF
  struct _EXCEPTION_REGISTRATION_RECORD *v17; // [esp+40h] [ebp-Ch]
  void *v18; // [esp+44h] [ebp-8h]
  int v19; // [esp+48h] [ebp-4h]

  v19 = -1;
  ExceptionList = NtCurrentTeb()->NtTib.ExceptionList;
  v18 = &_ehhandler__ReadMessageData_idMsgChannel__AAE_NAAVidBitMsg__ABV2__Z;
  v17 = ExceptionList;
  v4 = msg;
  Bits = idBitMsg::ReadBits(msg, -16);
  maxSize = out->maxSize;
  if ( Bits <= maxSize )
    out->curSize = Bits;
  else
    out->curSize = maxSize;
  idFile_BitMsg::idFile_BitMsg(&file, v4);
  compressor = this->compressor;
  v9 = compressor->__vftable;
  v19 = 0;
  v9->Init(compressor, &file, 0, 3);
  this->compressor->Read(this->compressor, out->writeData, out->curSize);
  this->incomingCompression = this->compressor->GetCompressionRatio(this->compressor);
  out->readCount = 0;
  out->readBit = 0;
  v10 = idBitMsg::ReadBits(out, 32);
  if ( this->reliableSend.first <= v10 )
  {
    while ( idMsgQueue::Get(&this->reliableSend, 0, 0, (int *)&msg, 1) && this->reliableSend.first <= v10 )
      ;
  }
  v11 = (__int16)idBitMsg::ReadBits(out, -16);
  v12 = (__int16)v11 <= 0;
  msg = (idBitMsg *)(__int16)v11;
  if ( (_WORD)v11 )
  {
    while ( !v12 && v11 <= out->curSize - out->readCount )
    {
      if ( idBitMsg::ReadBits(out, 32) == this->reliableReceive.last + 1 )
        idMsgQueue::Add(&this->reliableReceive, &out->writeData[out->readCount], (const int)msg, 1);
      idBitMsg::ReadData(out, 0, (int)msg);
      v11 = (__int16)idBitMsg::ReadBits(out, -16);
      v12 = (__int16)v11 <= 0;
      msg = (idBitMsg *)(__int16)v11;
      if ( !(_WORD)v11 )
        goto LABEL_13;
    }
    v14 = *(_DWORD *)common.type;
    v15 = Sys_NetAdrToString(this->remoteAddress);
    (*(void (**)(netadrtype_t, const char *, ...))(v14 + 124))(common.type, "%s: bad reliable message\n", v15);
    v19 = -1;
    idFile_BitMsg::~idFile_BitMsg(&file);
    return 0;
  }
  else
  {
LABEL_13:
    v19 = -1;
    idFile_BitMsg::~idFile_BitMsg(&file);
    return 1;
  }
}

// FUNC: public: void __thiscall idMsgChannel::SendNextFragment(class idPort &,int)
void __thiscall idMsgChannel::SendNextFragment(idMsgChannel *this, idPort *port, int time)
{
  int id; // edx
  int unsentFragmentStart; // ecx
  int curSize; // eax
  int v7; // edi
  int v8; // ebp
  idBitMsg msg; // [esp+Ch] [ebp-59Ch] BYREF
  unsigned __int8 msgBuf[1400]; // [esp+30h] [ebp-578h] BYREF

  idBitMsg::idBitMsg(&msg);
  if ( this->remoteAddress.type && this->unsentFragments )
  {
    id = this->id;
    msg.readData = msgBuf;
    msg.writeData = msgBuf;
    msg.maxSize = 1400;
    msg.numValueOverflows = 0;
    idBitMsg::WriteBits(&msg, id, -16);
    idBitMsg::WriteBits(&msg, this->outgoingSequence | 0x80000000, 32);
    unsentFragmentStart = this->unsentFragmentStart;
    curSize = this->unsentMsg.curSize;
    v7 = 1300;
    if ( unsentFragmentStart + 1300 > curSize )
      v7 = curSize - unsentFragmentStart;
    idBitMsg::WriteBits(&msg, this->unsentFragmentStart, -16);
    idBitMsg::WriteBits(&msg, v7, -16);
    idBitMsg::WriteData(&msg, &this->unsentMsg.writeData[this->unsentFragmentStart], v7);
    idPort::SendPacket(port, this->remoteAddress, msg.writeData, msg.curSize);
    v8 = msg.curSize;
    idMsgChannel::UpdateOutgoingRate(this, time, msg.curSize);
    if ( net_channelShowPackets.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%d send %4i : s = %i fragment = %i,%i\n",
        this->id,
        v8,
        this->outgoingSequence,
        this->unsentFragmentStart,
        v7);
    this->unsentFragmentStart += v7;
    if ( this->unsentFragmentStart == this->unsentMsg.curSize && v7 != 1300 )
    {
      ++this->outgoingSequence;
      this->unsentFragments = 0;
    }
  }
}

// FUNC: public: int __thiscall idMsgChannel::SendMessageA(class idPort &,int,class idBitMsg const &)
int __thiscall idMsgChannel::SendMessageA(idMsgChannel *this, idPort *port, int time, const idBitMsg *msg)
{
  int curSize; // edi
  int v7; // ecx

  if ( this->remoteAddress.type == NA_BAD || this->remoteAddress.type == NA_FAKE )
    return -1;
  if ( this->unsentFragments )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 152))(
      common.type,
      "idMsgChannel::SendMessage: called with unsent fragments left");
    return -1;
  }
  curSize = msg->curSize;
  v7 = idMsgQueue::GetTotalSize(&this->reliableSend) + curSize + 8;
  if ( v7 > 0x4000 )
  {
    (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
      common.type,
      "idMsgChannel::SendMessage: message too large, length = %i\n",
      v7);
    return -1;
  }
  this->unsentMsg.writeData = this->unsentBuffer;
  this->unsentMsg.readData = this->unsentBuffer;
  this->unsentMsg.maxSize = 0x4000;
  this->unsentMsg.numValueOverflows = 0;
  this->unsentMsg.curSize = 0;
  this->unsentMsg.overflowed = 0;
  this->unsentMsg.writeBit = 0;
  if ( v7 < 1300 )
  {
    idBitMsg::WriteBits(&this->unsentMsg, this->id, -16);
    idBitMsg::WriteBits(&this->unsentMsg, this->outgoingSequence, 32);
    idMsgChannel::WriteMessageData(this, &this->unsentMsg, msg);
    idPort::SendPacket(port, this->remoteAddress, this->unsentMsg.writeData, this->unsentMsg.curSize);
    idMsgChannel::UpdateOutgoingRate(this, time, this->unsentMsg.curSize);
    if ( net_channelShowPackets.internalVar->integerValue )
      (*(void (**)(netadrtype_t, const char *, ...))(*(_DWORD *)common.type + 124))(
        common.type,
        "%d send %4i : s = %i ack = %i\n",
        this->id,
        this->unsentMsg.curSize,
        this->outgoingSequence,
        this->incomingSequence);
    return this->outgoingSequence++;
  }
  else
  {
    this->unsentFragments = 1;
    this->unsentFragmentStart = 0;
    idMsgChannel::WriteMessageData(this, &this->unsentMsg, msg);
    idMsgChannel::SendNextFragment(this, port, time);
    return this->outgoingSequence;
  }
}

// FUNC: public: bool __thiscall idMsgChannel::Process(struct netadr_t,int,class idBitMsg &,int &)
bool __thiscall idMsgChannel::Process(idMsgChannel *this, const netadr_t from, int time, idBitMsg *msg, int *sequence)
{
  int Bits; // eax
  int v8; // ebx
  int v9; // ecx
  int incomingSequence; // ecx
  int v11; // edi
  const char *v12; // eax
  int v14; // ebp
  int v15; // ebx
  const char *v16; // eax
  int v17; // ebp
  int fragmentLength; // ecx
  int v19; // edi
  const char *v20; // eax
  int readCount; // eax
  int v22; // edi
  const char *v23; // eax
  int v24; // edx
  int v25; // [esp-8h] [ebp-40h]
  int v26; // [esp-4h] [ebp-3Ch]
  int v27; // [esp-4h] [ebp-3Ch]
  int v28; // [esp-4h] [ebp-3Ch]
  int v29; // [esp-4h] [ebp-3Ch]
  int fragLength; // [esp+10h] [ebp-28h]
  idBitMsg fragMsg; // [esp+14h] [ebp-24h] BYREF
  int fragStart; // [esp+3Ch] [ebp+4h]
  char msga; // [esp+4Ch] [ebp+14h]

  idBitMsg::idBitMsg(&fragMsg);
  if ( this->remoteAddress.port != from.port )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 124))(
      common.type,
      "idMsgChannel::Process: fixing up a translated port\n");
    this->remoteAddress.port = from.port;
  }
  idMsgChannel::UpdateIncomingRate(this, time, msg->curSize);
  Bits = idBitMsg::ReadBits(msg, 32);
  *sequence = Bits;
  if ( Bits >= 0 )
  {
    v8 = 0;
    msga = 0;
    fragStart = 0;
  }
  else
  {
    *sequence = Bits & 0x7FFFFFFF;
    msga = 1;
    fragStart = (__int16)idBitMsg::ReadBits(msg, -16);
    v8 = (__int16)idBitMsg::ReadBits(msg, -16);
  }
  fragLength = v8;
  if ( net_channelShowPackets.internalVar->integerValue )
  {
    v9 = *(_DWORD *)common.type;
    if ( msga )
      (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(
        common.type,
        "%d recv %4i : s = %i fragment = %i,%i\n",
        this->id,
        msg->curSize,
        *sequence,
        fragStart,
        v8);
    else
      (*(void (**)(netadrtype_t, const char *, ...))(v9 + 124))(
        common.type,
        "%d recv %4i : s = %i\n",
        this->id,
        msg->curSize,
        *sequence);
  }
  incomingSequence = this->incomingSequence;
  if ( *sequence > incomingSequence )
  {
    v14 = *sequence - incomingSequence - 1;
    if ( v14 <= 0 )
    {
      v17 = time;
    }
    else
    {
      if ( net_channelShowDrop.internalVar->integerValue || net_channelShowPackets.internalVar->integerValue )
      {
        v15 = *(_DWORD *)common.type;
        v27 = *sequence;
        v16 = Sys_NetAdrToString(this->remoteAddress);
        (*(void (**)(netadrtype_t, const char *, ...))(v15 + 124))(
          common.type,
          "%s: dropped %i packets at %i\n",
          v16,
          v14,
          v27);
        v8 = fragLength;
      }
      v28 = v14;
      v17 = time;
      idMsgChannel::UpdatePacketLoss(this, time, 0, v28);
    }
    if ( msga )
    {
      if ( *sequence != this->fragmentSequence )
      {
        this->fragmentSequence = *sequence;
        this->fragmentLength = 0;
      }
      fragmentLength = this->fragmentLength;
      if ( fragStart != fragmentLength )
      {
        if ( net_channelShowDrop.internalVar->integerValue || net_channelShowPackets.internalVar->integerValue )
        {
          v19 = *(_DWORD *)common.type;
          v29 = *sequence;
          v20 = Sys_NetAdrToString(this->remoteAddress);
          (*(void (**)(netadrtype_t, const char *, ...))(v19 + 124))(
            common.type,
            "%s: dropped a message fragment at seq %d\n",
            v20,
            v29);
        }
LABEL_28:
        idMsgChannel::UpdatePacketLoss(this, v17, 0, 1);
        return 0;
      }
      if ( v8 < 0
        || (readCount = msg->readCount, v8 > msg->curSize - readCount)
        || (unsigned int)(v8 + fragmentLength) > 0x4000 )
      {
        if ( net_channelShowDrop.internalVar->integerValue || net_channelShowPackets.internalVar->integerValue )
        {
          v22 = *(_DWORD *)common.type;
          v23 = Sys_NetAdrToString(this->remoteAddress);
          (*(void (**)(netadrtype_t, const char *, ...))(v22 + 124))(common.type, "%s: illegal fragment length\n", v23);
        }
        goto LABEL_28;
      }
      ((void (__stdcall *)(unsigned __int8 *, int))SIMDProcessor->Memcpy)(&msg->writeData[readCount], v8);
      this->fragmentLength += v8;
      idMsgChannel::UpdatePacketLoss(this, time, 1, 0);
      if ( v8 == 1300 )
        return 0;
    }
    else
    {
      ((void (__stdcall *)(unsigned __int8 *, int))SIMDProcessor->Memcpy)(
        &msg->writeData[msg->readCount],
        msg->curSize - msg->readCount);
      this->fragmentLength = msg->curSize - msg->readCount;
      idMsgChannel::UpdatePacketLoss(this, v17, 1, 0);
    }
    v24 = *sequence;
    fragMsg.writeData = this->fragmentBuffer;
    fragMsg.readData = this->fragmentBuffer;
    fragMsg.maxSize = this->fragmentLength;
    fragMsg.curSize = fragMsg.maxSize;
    memset(&fragMsg.readCount, 0, 12);
    this->incomingSequence = v24;
    return idMsgChannel::ReadMessageData(this, msg, &fragMsg) != 0;
  }
  if ( net_channelShowDrop.internalVar->integerValue || net_channelShowPackets.internalVar->integerValue )
  {
    v11 = *(_DWORD *)common.type;
    v26 = this->incomingSequence;
    v25 = *sequence;
    v12 = Sys_NetAdrToString(this->remoteAddress);
    (*(void (**)(netadrtype_t, const char *, ...))(v11 + 124))(
      common.type,
      "%s: out of order packet %i at %i\n",
      v12,
      v25,
      v26);
  }
  return 0;
}

// FUNC: public: bool __thiscall idMsgChannel::SendReliableMessage(class idBitMsg const &)
bool __thiscall idMsgChannel::SendReliableMessage(idMsgChannel *this, const idBitMsg *msg)
{
  bool result; // al

  if ( this->remoteAddress.type == NA_BAD )
    return 0;
  if ( this->remoteAddress.type == NA_FAKE )
    return 1;
  result = idMsgQueue::Add(&this->reliableSend, msg->readData, msg->curSize, 1);
  if ( !result )
  {
    (*(void (__cdecl **)(netadrtype_t, const char *))(*(_DWORD *)common.type + 136))(
      common.type,
      "idMsgChannel::SendReliableMessage: overflowed");
    return 0;
  }
  return result;
}

// FUNC: public: bool __thiscall idMsgChannel::GetReliableMessage(class idBitMsg &)
int __thiscall idMsgChannel::GetReliableMessage(idMsgChannel *this, idBitMsg *msg)
{
  idBitMsg *v2; // esi
  int result; // eax
  int maxSize; // ecx

  v2 = msg;
  LOBYTE(result) = idMsgQueue::Get(&this->reliableReceive, msg->writeData, msg->maxSize, (int *)&msg, 1);
  maxSize = v2->maxSize;
  if ( (int)msg <= maxSize )
    v2->curSize = (int)msg;
  else
    v2->curSize = maxSize;
  v2->readCount = 0;
  v2->readBit = 0;
  return result;
}

//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//

#pragma once

#include "HDMCDef.h"

namespace Harlinn::Windows::DirectX::MiniEngine
{

    class CommandContext;
    class RootSignature;
    class VertexShader;
    class GeometryShader;
    class HullShader;
    class DomainShader;
    class PixelShader;
    class ComputeShader;

    class PSO
    {
    protected:
        const wchar_t* m_Name;
        const RootSignature* m_RootSignature = nullptr;
        D3D12PipelineState m_PSO;
    public:
        PSO( const wchar_t* Name ) 
            : m_Name( Name ), m_RootSignature( nullptr ) 
        {}

        HDMC_EXPORT static void DestroyAll( void );

        void SetRootSignature( const RootSignature& BindMappings )
        {
            m_RootSignature = &BindMappings;
        }

        const RootSignature& GetRootSignature( void ) const
        {
            ASSERT( m_RootSignature != nullptr );
            return *m_RootSignature;
        }

        const D3D12PipelineState& GetPipelineStateObject( void ) const 
        { 
            return m_PSO; 
        }
    };

    class GraphicsPSO : public PSO
    {
        friend class CommandContext;
    private:

        D3D12_GRAPHICS_PIPELINE_STATE_DESC m_PSODesc;
        std::shared_ptr<const D3D12_INPUT_ELEMENT_DESC> m_InputLayouts;
    public:

        // Start with empty state
        HDMC_EXPORT GraphicsPSO( const wchar_t* Name = L"Unnamed Graphics PSO" );

        HDMC_EXPORT void SetBlendState( const D3D12_BLEND_DESC& BlendDesc );
        HDMC_EXPORT void SetRasterizerState( const D3D12_RASTERIZER_DESC& RasterizerDesc );
        HDMC_EXPORT void SetDepthStencilState( const D3D12_DEPTH_STENCIL_DESC& DepthStencilDesc );
        HDMC_EXPORT void SetSampleMask( UINT SampleMask );
        HDMC_EXPORT void SetPrimitiveTopologyType( D3D12_PRIMITIVE_TOPOLOGY_TYPE TopologyType );
        HDMC_EXPORT void SetDepthTargetFormat( DXGI_FORMAT DSVFormat, UINT MsaaCount = 1, UINT MsaaQuality = 0 );
        HDMC_EXPORT void SetRenderTargetFormat( DXGI_FORMAT RTVFormat, DXGI_FORMAT DSVFormat, UINT MsaaCount = 1, UINT MsaaQuality = 0 );
        HDMC_EXPORT void SetRenderTargetFormats( UINT NumRTVs, const DXGI_FORMAT* RTVFormats, DXGI_FORMAT DSVFormat, UINT MsaaCount = 1, UINT MsaaQuality = 0 );
        HDMC_EXPORT void SetInputLayout( UINT NumElements, const D3D12_INPUT_ELEMENT_DESC* pInputElementDescs );
        HDMC_EXPORT void SetPrimitiveRestart( D3D12_INDEX_BUFFER_STRIP_CUT_VALUE IBProps );

        // These const_casts shouldn't be necessary, but we need to fix the API to accept "const void* pShaderBytecode"
        void SetVertexShader( const void* Binary, size_t Size ) { m_PSODesc.VS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }
        void SetPixelShader( const void* Binary, size_t Size ) { m_PSODesc.PS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }
        void SetGeometryShader( const void* Binary, size_t Size ) { m_PSODesc.GS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }
        void SetHullShader( const void* Binary, size_t Size ) { m_PSODesc.HS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }
        void SetDomainShader( const void* Binary, size_t Size ) { m_PSODesc.DS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }

        void SetVertexShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.VS = Binary; }
        void SetPixelShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.PS = Binary; }
        void SetGeometryShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.GS = Binary; }
        void SetHullShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.HS = Binary; }
        void SetDomainShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.DS = Binary; }

        // Perform validation and compute a hash value for fast state block comparisons
        HDMC_EXPORT void Finalize( );

    };


    class ComputePSO : public PSO
    {
        friend class CommandContext;

    private:
        D3D12_COMPUTE_PIPELINE_STATE_DESC m_PSODesc;
    public:
        HDMC_EXPORT ComputePSO( const wchar_t* Name = L"Unnamed Compute PSO" );

        void SetComputeShader( const void* Binary, size_t Size ) { m_PSODesc.CS = CD3DX12_SHADER_BYTECODE( const_cast< void* >( Binary ), Size ); }
        void SetComputeShader( const D3D12_SHADER_BYTECODE& Binary ) { m_PSODesc.CS = Binary; }

        HDMC_EXPORT void Finalize( );

    };
}
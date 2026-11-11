import {
	BellAlertIcon,
	MagnifyingGlassIcon,
	ServerStackIcon,
	SignalIcon,
} from "@heroicons/react/24/outline";
import type { ComponentType, SVGProps } from "react";

type IconComponent = ComponentType<SVGProps<SVGSVGElement>>;

export const NAV_LINKS = [
	{ label: "기능", href: "#features" },
	{ label: "가격", href: "#pricing" },
	{ label: "FAQ", href: "#faq" },
] as const;

export interface Feature {
	id: string;
	icon: IconComponent;
	name: string;
	title: string;
	body: string;
	snippet: string;
}

export const FEATURES: Feature[] = [
	{
		id: "collect",
		icon: ServerStackIcon,
		name: "수집",
		title: "DaemonSet 하나로 끝나는 수집",
		body: "경량 에이전트를 Helm 차트로 배포하면 파드·노드·컨테이너 로그가 쿠버네티스 라벨과 함께 들어옵니다. 압축된 청크는 S3 호환 오브젝트 스토리지에 쌓여 보관 비용이 낮습니다.",
		snippet: "helm install driftlog-agent driftlog/agent",
	},
	{
		id: "search",
		icon: MagnifyingGlassIcon,
		name: "검색",
		title: "익숙한 LogQL 스타일 쿼리",
		body: "라벨로 범위를 좁히고 |= 와 정규식으로 본문을 거릅니다. Grafana 데이터소스로 연결하면 기존 대시보드에서도 같은 쿼리를 그대로 씁니다.",
		snippet: '{app="checkout"} |= "timeout"',
	},
	{
		id: "tail",
		icon: SignalIcon,
		name: "라이브 테일",
		title: "배포 직후를 실시간으로",
		body: "쿼리 결과를 그대로 스트리밍합니다. 롤아웃 중 새로 뜬 파드의 로그를 터미널에서 tail -f 하듯 따라가며 볼 수 있습니다.",
		snippet: "driftlog tail '{ns=\"prod\"}'",
	},
	{
		id: "alert",
		icon: BellAlertIcon,
		name: "알림",
		title: "에러가 급증하면 Slack으로",
		body: "쿼리 결과의 개수나 비율에 임계치를 걸어 두면, 평소보다 에러가 늘어나는 순간 문제 로그 샘플과 함께 Slack 채널에 알립니다.",
		snippet: 'sum(rate({level="error"}[5m])) > 20',
	},
];

export const STATS = [
	{
		value: "2TB",
		label: "하루 수집량",
		detail: "단일 클러스터, 에이전트 120대 기준",
	},
	{
		value: "1.2초",
		label: "쿼리 p95 응답",
		detail: "최근 24시간 범위, 라벨 필터 포함",
	},
	{
		value: "70%",
		label: "저장 비용 절감",
		detail: "전문 인덱싱 기반 스택 대비",
	},
] as const;

export interface Plan {
	id: string;
	name: string;
	summary: string;
	price: string;
	period?: string;
	cta: string;
	isRecommended?: boolean;
	features: string[];
}

export const PLANS: Plan[] = [
	{
		id: "free",
		name: "Free",
		summary: "개인 프로젝트와 PoC를 위한 요금제",
		price: "0원",
		period: "/월",
		cta: "무료로 시작",
		features: [
			"하루 5GB 수집",
			"7일 보관",
			"라이브 테일·Slack 알림",
			"커뮤니티 지원",
		],
	},
	{
		id: "team",
		name: "Team",
		summary: "5~200명 규모 엔지니어링 팀을 위한 요금제",
		price: "49,000원",
		period: "/월",
		cta: "Team으로 시작",
		isRecommended: true,
		features: [
			"하루 50GB 수집",
			"30일 보관",
			"알림 규칙·사용자 수 제한 없음",
			"Grafana 데이터소스 연동",
			"영업일 기준 이메일 지원",
		],
	},
	{
		id: "enterprise",
		name: "Enterprise",
		summary: "규정 준수와 대규모 트래픽이 필요한 조직",
		price: "문의",
		cta: "영업팀에 문의",
		features: [
			"수집량 무제한",
			"1년 이상 보관",
			"SSO(SAML·OIDC)와 감사 로그",
			"자체 호스팅·고객 소유 버킷",
			"전담 엔지니어 지원",
		],
	},
];

export const FAQS = [
	{
		id: "self-hosting",
		question: "자체 호스팅도 가능한가요?",
		answer:
			"Enterprise 요금제에서 지원합니다. 같은 에이전트와 쿼리 엔진을 Helm 차트로 사내 쿠버네티스 클러스터에 설치하고, 로그는 사내 S3 호환 스토리지(MinIO 등)에 저장합니다. 업데이트는 클라우드 버전과 같은 주기로 제공됩니다.",
	},
	{
		id: "compat",
		question: "이미 Loki와 Vector를 쓰고 있어요. 그대로 연결할 수 있나요?",
		answer:
			"네. Vector의 loki sink나 Promtail 설정에서 엔드포인트와 토큰만 Driftlog로 바꾸면 됩니다. 쿼리 문법이 LogQL과 거의 같아서 기존 대시보드와 알림 규칙도 대부분 그대로 옮겨집니다.",
	},
	{
		id: "region",
		question: "데이터는 어디에 저장되나요?",
		answer:
			"기본 저장 위치는 서울 리전의 오브젝트 스토리지이며, 전송과 저장 모두 암호화됩니다. Team부터는 도쿄·프랑크푸르트 등 다른 리전을 고를 수 있고, Enterprise에서는 고객 소유 버킷에 바로 저장할 수 있습니다.",
	},
	{
		id: "overage",
		question: "하루 수집량을 넘기면 어떻게 되나요?",
		answer:
			"수집은 멈추지 않습니다. 한도의 80%와 100%에 도달하면 이메일과 Slack으로 알려 드리고, Team 초과분은 GB당 1,200원으로 다음 달에 정산됩니다. Free 요금제는 한도를 넘은 날 남은 시간 동안 10% 샘플링으로 수집합니다.",
	},
] as const;

export const FOOTER_GROUPS = [
	{
		title: "제품",
		links: [
			{ label: "기능", href: "#features" },
			{ label: "가격", href: "#pricing" },
			{ label: "변경 기록", href: "#" },
		],
	},
	{
		title: "리소스",
		links: [
			{ label: "문서", href: "#" },
			{ label: "쿼리 레퍼런스", href: "#" },
			{ label: "상태 페이지", href: "#" },
		],
	},
	{
		title: "회사",
		links: [
			{ label: "소개", href: "#" },
			{ label: "블로그", href: "#" },
			{ label: "개인정보처리방침", href: "#" },
		],
	},
] as const;
